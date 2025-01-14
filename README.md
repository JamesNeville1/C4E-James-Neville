# C++ for Engines

### This is my project for my C++ for Engines module. This project is a framework, therefore it doesn't have much in the way of animation or graphics. The aim of this project was to make a system that can be built upon by designers.
<br /><br />

(My code can be found [here](https://github.com/JamesNeville1/C4E-James-Neville/tree/main/Source/C4E_Neville))

<br /><br />

In this project, Tick is rarely used and I have made an optimal and easily built upon system. This framework was built for a puzzle game.
<br /><br />

## Anonymous Modular Design (AMD)
![](https://github.com/JamesNeville1/C4E-James-Neville/blob/main/AMD.png)
For this project, we were tasked with using the AMD design pattern, more about what AMD is can be found [here](https://izzet-dev.itch.io/the-gangs-all-here). In short AMD has three principles:
<br />
- When going up the hierarchy, use events
- When going down the hierarchy, use functions
- When going outside of the hierarchy, use interfaces
<br /><br />

This doesn't mean you can't use interfaces when you should use function, but you have to use interfaces where you would use interfaces

I designed this diagram at the start of the project to ensure my hierarchy was optimal.

## Game Mode
The execution order was thought out heavily. To setup the game, three different functions are run:
- BeginPlay
- HandleMatchIsWaitingToStart
- DelayedBeginPlay
```
private:
  //Before "BeginPlay"
  virtual void HandleMatchIsWaitingToStart() override;
  //After "BeginPlay"
  void DelayedBeginPlay(bool played);
```
(BeginPlay isn't used in code, designers can still use it though)
<br /><br />
This is done in the interest of simplifying the development process. 
Certain things will need to run before and after BeginPlay to be setup correctly. 
For example, the Game Rules need to gather their corresponding actors (which happens on BeginPlay) before the UI can be setup. 
<br /><br />
Due to this, we don't have to meticulously pay attention to the execution of different actors, it doesn't matter when the Game Rule finds each item because the UI will always look when it is finished.
<br /><br />
Throughout the code, there are a lot of hooks for the designers to use when inheriting in Blueprint.
```
//Hooks
UFUNCTION(BlueprintNativeEvent, DisplayName = "On Guys Spawned")
void RecieveGuysSpawned(const TArray<AP_Guy*>& guys);
UFUNCTION(BlueprintNativeEvent, DisplayName = "On Game Rule Setup")
void RecieveGameRuleSetup();
UFUNCTION(BlueprintNativeEvent, DisplayName = "On Controller Setup")
void RecieveControllerSetup();
UFUNCTION(BlueprintNativeEvent, DisplayName = "On Level Manager Setup")
void RecieveLevelManagerSetup();
UFUNCTION(BlueprintNativeEvent, DisplayName = "On Late Begin Play")
void RecieveDelayedBeginPlay();
UFUNCTION(BlueprintNativeEvent, DisplayName = "On Fail Level")
void RecieveFailLevel();
UFUNCTION(BlueprintNativeEvent, DisplayName = "On End Level")
void RecieveEndLevel();
UFUNCTION(BlueprintNativeEvent, DisplayName = "On End Game")
void RecieveEndGame();
UFUNCTION(BlueprintNativeEvent, DisplayName = "On Candy Game Rule Complete")
void RecieveCandyGameRuleComplete();
UFUNCTION(BlueprintNativeEvent, DisplayName = "On Pumpkin Game Rule Complete")
void RecievePumpkinGameRuleComplete();
UFUNCTION(BlueprintNativeEvent, DisplayName = "On Timer Game Rule Complete")
void RecieveTimerGameRuleComplete();
UFUNCTION(BlueprintNativeEvent, DisplayName = "On Player Out of Lives")
void RecievePlayerOutOfLives(const AP_Guy* guyThatDied);
```
All of these were thoughout, giving designers complete freedom to prune off of my system.
<br /><br />

For example, after setting up each GameRule I give the designers the ability to write their own code straight after in Blueprint. This way, they can setup their own GameRules.
```
//GRs with setups, can be done with begin play, but allows me to controller the execution order
_CandyGRRef = Cast<UGR_Candy>(GetComponentByClass(UGR_Candy::StaticClass()));
if (_CandyGRRef != nullptr)
{
  _CandyGRRef->Setup(this);
}

_PumpkinGRRef = Cast<UGR_Pumpkin>(GetComponentByClass(UGR_Pumpkin::StaticClass()));
if (_PumpkinGRRef != nullptr)
{
  _PumpkinGRRef->Setup(this);
}

_HasTimer = GetComponentByClass(UGR_Timer::StaticClass()) != nullptr;

RecieveGameRuleSetup();
```
<br /><br />

I also go one step further, by giving the designers access to specific scripts. This has to be heavily thought through, as certain scripts adjust things that designers may not know about.
```
//Designers may call these
UFUNCTION(BlueprintCallable)
void FailLevel();
UFUNCTION(BlueprintCallable)
void EndLevel();

//Designers may not call these
UFUNCTION()
void Handle_CandyGameRuleComplete();
UFUNCTION()
void Handle_TimerGameRuleComplete();
UFUNCTION()
void Handle_PumpkinGameRuleComplete();
UFUNCTION()
void PlayerOutOfLives(AP_Guy* guyThatDied);
```
From this snippet, you can see that the designer CAN finish and fail the level. What this does is obvious to the designer and should not break. 
On the other hand, the functions bellow cause very specific changes that I do NOT want to be called by the designer. For example, the Handle_CandyGameRuleComplete() function will only be called by an event inside the Candy Game Rule.
If the designer were to call this function, it would reduce a counter by one that checks if all other game rules have been complete, making the Game Mode react erroneously.

## Guy (Player)
The 'Guy' class is used to make different characters for the level. Currently, the framework has three characters: Lil Guy, Big Guy, Strong Guy. These characters are fairly simple but a designer could add complexity to the class rather easily.

Here is an example of me using AMD to go up to the controller:
```
OnSwapGuy.AddUniqueDynamic(controller, &APC_Guy::SwapCharacter);
OnRespawnAlertCheck.AddUniqueDynamic(controller, &APC_Guy::RespawnCheck);
OnDamageUIAlert.AddUniqueDynamic(controller, &APC_Guy::UpdateHealthAlert);
```
As you can see, I have a few events inside the Guy class that call functions inside the controller.
The first tells the controller to swap to the next character, the one after that tells the controller to check if we can respawn (are we out of lives?), and lastly we also tell the controller to alert the UI to update health when we take damage.



## Buttons and Level Pieces
Each button has a button component which holds all actors it intends to tell to turn off or on.
```
UPROPERTY(EditAnywhere, BlueprintReadOnly)
TArray<AActor*> _LevelPieces;

UFUNCTION()
void Press();
UFUNCTION()
void UnPress();
```
Because it is a component, we can have different types of buttons. In my framework, I have a floor button that turns on when someone steps on it, and off when they step off. I also have a normal button that has to be pressed again to toggle between on and off.

<br /><br />

We then just send a signal to each actor in the array when turned off and on.
```
void UButtonComponent::Press()
{
	for (AActor* levelPiece : _LevelPieces)
	{
		ILevelPiece::Execute_Trigger(levelPiece);
	}
}

void UButtonComponent::UnPress()
{
	for (AActor* levelPiece : _LevelPieces)
	{
		ILevelPiece::Execute_Reverse(levelPiece);
	}
}
```
Here shows my preference to use composition over inheritance. Inheritance is good, but can become hard to maintain as time goes on. 
Because I have an interface, any object of any class can be a "Level Piece", they don't have to conform to a specific class allowing this framework to be utilized easier.

<br /><br />

Here you can see how simple it is to add new logic. I simply tell the platform to move to one possition or another. This is very modular and has a variety of applications
```
void AMovingPlatform::Trigger_Implementation()
{
	_TargetPos = _OnPos;
	SetActorTickEnabled(true);
}

void AMovingPlatform::Reverse_Implementation()
{
	_TargetPos = _OffPos;
	SetActorTickEnabled(true);
}
```
