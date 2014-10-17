// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "BlueprintGraphPrivatePCH.h"
#include "K2Node_InputKeyEvent.h"
#include "CompilerResultsLog.h"
#include "KismetCompiler.h"
#include "BlueprintNodeSpawner.h"
#include "EditorCategoryUtils.h"
#include "BlueprintEditorUtils.h"
#include "EdGraphSchema_K2.h"
#include "BlueprintActionDatabaseRegistrar.h"

#define LOCTEXT_NAMESPACE "UK2Node_InputKey"

UK2Node_InputKey::UK2Node_InputKey(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bConsumeInput = true;
	bOverrideParentBinding = true;
}

void UK2Node_InputKey::PostLoad()
{
	Super::PostLoad();

	if (GetLinkerUE4Version() < VER_UE4_BLUEPRINT_INPUT_BINDING_OVERRIDES)
	{
		// Don't change existing behaviors
		bOverrideParentBinding = false;
	}
}

void UK2Node_InputKey::AllocateDefaultPins()
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	CreatePin(EGPD_Output, K2Schema->PC_Exec, TEXT(""), NULL, false, false, TEXT("Pressed"));
	CreatePin(EGPD_Output, K2Schema->PC_Exec, TEXT(""), NULL, false, false, TEXT("Released"));

	Super::AllocateDefaultPins();
}

FLinearColor UK2Node_InputKey::GetNodeTitleColor() const
{
	return GetDefault<UGraphEditorSettings>()->EventNodeTitleColor;
}

FName UK2Node_InputKey::GetModifierName() const
{
	if ( bControl && !bAlt && !bShift && !bCommand )
	{
		return FName("Ctrl");
	}
	else if ( bControl && bAlt && !bShift && !bCommand )
	{
		return FName("Ctrl+Alt");
	}
	else if ( bControl && !bAlt && bShift && !bCommand )
	{
		return FName("Ctrl+Shift");
	}
	else if ( bControl && !bAlt && !bShift && bCommand )
	{
		return FName("Ctrl+Cmd");
	}
	else if ( bControl && bAlt && bShift && !bCommand )
	{
		return FName("Ctrl+Alt+Shift");
	}
	else if ( bControl && bAlt && !bShift && bCommand )
	{
		return FName("Ctrl+Cmd+Alt");
	}
	else if ( bControl && !bAlt && bShift && bCommand )
	{
		return FName("Ctrl+Cmd+Shift");
	}
	else if ( !bControl && bAlt && bShift && bCommand )
	{
		return FName("Cmd+Alt+Shift");
	}
	else if ( bControl && bAlt && bShift && bCommand )
	{
		return FName("Ctrl+Cmd+Alt+Shift");
	}
	else if ( !bControl && bAlt && !bShift && !bCommand )
	{
		return FName("Alt");
	}
	else if ( !bControl && bAlt && bShift && !bCommand )
	{
		return FName("Alt+Shift");
	}
	else if ( !bControl && bAlt && !bShift && bCommand )
	{
		return FName("Cmd+Alt");
	}
	else if ( !bControl && !bAlt && bShift && bCommand )
	{
		return FName("Cmd+Shift");
	}
	else if ( !bControl && !bAlt && bShift && !bCommand )
	{
		return FName("Shift");
	}
	else if ( !bControl && !bAlt && !bShift && bCommand )
	{
		return FName("Cmd");
	}

	return NAME_None;
}

FText UK2Node_InputKey::GetModifierText() const
{
	//@todo This should be unified with other places in the editor [10/11/2013 justin.sargent]
	if ( bControl && !bAlt && !bShift && !bCommand )
	{
#if PLATFORM_MAC
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Command", "Cmd");
#else
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Control", "Ctrl");
#endif
	}
	else if ( bControl && bAlt && !bShift && !bCommand )
	{
#if PLATFORM_MAC
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Command + KeyName_Alt", "Cmd+Alt");
#else
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Control + KeyName_Alt", "Ctrl+Alt");
#endif
	}
	else if ( bControl && !bAlt && bShift && !bCommand )
	{
#if PLATFORM_MAC
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Command + KeyName_Shift", "Cmd+Shift");
#else
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Control + KeyName_Shift", "Ctrl+Shift");
#endif
	}
	else if ( bControl && !bAlt && !bShift && bCommand )
	{
#if PLATFORM_MAC
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Command + KeyName_Control", "Cmd+Ctrl");
#else
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Control + KeyName_Command", "Ctrl+Cmd");
#endif
	}
	else if ( !bControl && bAlt && !bShift && bCommand )
	{
#if PLATFORM_MAC
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Control + KeyName_Alt", "Ctrl+Alt");
#else
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Command + KeyName_Alt", "Cmd+Alt");
#endif
	}
	else if ( !bControl && !bAlt && bShift && bCommand )
	{
#if PLATFORM_MAC
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Control + KeyName_Shift", "Ctrl+Shift");
#else
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Command + KeyName_Shift", "Cmd+Shift");
#endif
	}
	else if ( bControl && bAlt && bShift && !bCommand )
	{
#if PLATFORM_MAC
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Command + KeyName_Alt + KeyName_Shift", "Cmd+Alt+Shift");
#else
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Control + KeyName_Alt + KeyName_Shift", "Ctrl+Alt+Shift");
#endif
	}
	else if ( bControl && bAlt && !bShift && bCommand )
	{
#if PLATFORM_MAC
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Command + KeyName_Control + KeyName_Alt", "Cmd+Ctrl+Alt");
#else
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Control + KeyName_Command + KeyName_Alt", "Ctrl+Cmd+Alt");
#endif
	}
	else if ( bControl && !bAlt && bShift && bCommand )
	{
#if PLATFORM_MAC
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Command + KeyName_Control + KeyName_Shift", "Cmd+Ctrl+Shift");
#else
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Control + KeyName_Command + KeyName_Shift", "Ctrl+Cmd+Shift");
#endif
	}
	else if ( bControl && bAlt && bShift && bCommand )
	{
#if PLATFORM_MAC
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Command + KeyName_Control + KeyName_Alt + KeyName_Shift", "Cmd+Ctrl+Alt+Shift");
#else
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Control + KeyName_Command + KeyName_Alt + KeyName_Shift", "Ctrl+Cmd+Alt+Shift");
#endif
	}
	else if ( !bControl && bAlt && !bShift && !bCommand )
	{
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Alt", "Alt");
	}
	else if ( !bControl && bAlt && bShift && !bCommand )
	{
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Alt + KeyName_Shift", "Alt+Shift");
	}
	else if ( !bControl && bAlt && !bShift && bCommand )
	{
#if PLATFORM_MAC
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Control + KeyName_Alt", "Ctrl+Alt");
#else
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Command + KeyName_Alt", "Cmd+Alt");
#endif
	}
	else if ( !bControl && !bAlt && bShift && !bCommand )
	{
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Shift", "Shift");
	}
	else if ( !bControl && !bAlt && !bShift && bCommand )
	{
		return NSLOCTEXT("UK2Node_InputKey", "KeyName_Command", "Cmd");
	}

	return FText::GetEmpty();
}

FText UK2Node_InputKey::GetKeyText() const
{
	return InputKey.GetDisplayName();
}

FText UK2Node_InputKey::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (bControl || bAlt || bShift)
	{
		if (CachedNodeTitle.IsOutOfDate())
		{
			FFormatNamedArguments Args;
			Args.Add(TEXT("ModifierKey"), GetModifierText());
			Args.Add(TEXT("Key"), GetKeyText());
			
			// FText::Format() is slow, so we cache this to save on performance
			CachedNodeTitle = FText::Format(NSLOCTEXT("K2Node", "InputKey_Name_WithModifiers", "{ModifierKey} {Key}"), Args);
		}
		return CachedNodeTitle;
	}
	else
	{
		return GetKeyText();
	}
}

FText UK2Node_InputKey::GetTooltipText() const
{
	if (CachedTooltip.IsOutOfDate())
	{
		FText ModifierText = GetModifierText();
		FText KeyText = GetKeyText();

		// FText::Format() is slow, so we cache this to save on performance
		if (!ModifierText.IsEmpty())
		{
			CachedTooltip = FText::Format(NSLOCTEXT("K2Node", "InputKey_Tooltip_Modifiers", "Events for when the {0} key is pressed or released while {1} is also held."), KeyText, ModifierText);
		}
		else
		{
			CachedTooltip = FText::Format(NSLOCTEXT("K2Node", "InputKey_Tooltip", "Events for when the {0} key is pressed or released."), KeyText);
		}
	}
	return CachedTooltip;
}

FName UK2Node_InputKey::GetPaletteIcon(FLinearColor& OutColor) const
{
	if (InputKey.IsMouseButton())
	{
		return TEXT("GraphEditor.MouseEvent_16x");
	}
	else if (InputKey.IsGamepadKey())
	{
		return TEXT("GraphEditor.PadEvent_16x");
	}
	else
	{
		return TEXT("GraphEditor.KeyEvent_16x");
	}
}

bool UK2Node_InputKey::IsCompatibleWithGraph(UEdGraph const* Graph) const
{
	UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForGraph(Graph);

	UEdGraphSchema_K2 const* K2Schema = Cast<UEdGraphSchema_K2>(Graph->GetSchema());
	bool const bIsConstructionScript = (K2Schema != nullptr) ? K2Schema->IsConstructionScript(Graph) : false;

	return (Blueprint != nullptr) && Blueprint->SupportsInputEvents() && !bIsConstructionScript && Super::IsCompatibleWithGraph(Graph);
}

UEdGraphPin* UK2Node_InputKey::GetPressedPin() const
{
	return FindPin(TEXT("Pressed"));
}

UEdGraphPin* UK2Node_InputKey::GetReleasedPin() const
{
	return FindPin(TEXT("Released"));
}

void UK2Node_InputKey::ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const
{
	Super::ValidateNodeDuringCompilation(MessageLog);
	
	if (!InputKey.IsValid())
	{
		MessageLog.Warning(*FText::Format(NSLOCTEXT("KismetCompiler", "Invalid_InputKey_Warning", "InputKey Event specifies invalid FKey'{0}' for @@"), FText::FromString(InputKey.ToString())).ToString(), this);
	}
	else if (InputKey.IsFloatAxis())
	{
		MessageLog.Warning(*FText::Format(NSLOCTEXT("KismetCompiler", "Axis_InputKey_Warning", "InputKey Event specifies axis FKey'{0}' for @@"), FText::FromString(InputKey.ToString())).ToString(), this);
	}
	else if (!InputKey.IsBindableInBlueprints())
	{
		MessageLog.Warning( *FText::Format( NSLOCTEXT("KismetCompiler", "NotBindanble_InputKey_Warning", "InputKey Event specifies FKey'{0}' that is not blueprint bindable for @@"), FText::FromString(InputKey.ToString())).ToString(), this);
	}
}

void UK2Node_InputKey::CreateInputKeyEvent(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UEdGraphPin* InputKeyPin, const EInputEvent KeyEvent)
{
	if (InputKeyPin->LinkedTo.Num() > 0)
	{
		UK2Node_InputKeyEvent* InputKeyEvent = CompilerContext.SpawnIntermediateNode<UK2Node_InputKeyEvent>(this, SourceGraph);
		const FName ModifierName = GetModifierName();
		if ( ModifierName != NAME_None )
		{
			InputKeyEvent->CustomFunctionName = FName( *FString::Printf(TEXT("InpActEvt_%s_%s_%s"), *ModifierName.ToString(), *InputKey.ToString(), *InputKeyEvent->GetName()));
		}
		else
		{
			InputKeyEvent->CustomFunctionName = FName( *FString::Printf(TEXT("InpActEvt_%s_%s"), *InputKey.ToString(), *InputKeyEvent->GetName()));
		}
		InputKeyEvent->InputChord.Key = InputKey;
		InputKeyEvent->InputChord.bCtrl = bControl;
		InputKeyEvent->InputChord.bAlt = bAlt;
		InputKeyEvent->InputChord.bShift = bShift;
		InputKeyEvent->InputChord.bCmd = bCommand;
		InputKeyEvent->bConsumeInput = bConsumeInput;
		InputKeyEvent->bExecuteWhenPaused = bExecuteWhenPaused;
		InputKeyEvent->bOverrideParentBinding = bOverrideParentBinding;
		InputKeyEvent->InputKeyEvent = KeyEvent;
		InputKeyEvent->EventSignatureName = TEXT("InputActionHandlerDynamicSignature__DelegateSignature");
		InputKeyEvent->EventSignatureClass = UInputComponent::StaticClass();
		InputKeyEvent->bInternalEvent = true;
		InputKeyEvent->AllocateDefaultPins();

		// Move any exec links from the InputActionNode pin to the InputActionEvent node
		UEdGraphPin* EventOutput = CompilerContext.GetSchema()->FindExecutionPin(*InputKeyEvent, EGPD_Output);

		if(EventOutput != NULL)
		{
			CompilerContext.MovePinLinksToIntermediate(*InputKeyPin, *EventOutput);
		}
	}
}

void UK2Node_InputKey::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	CreateInputKeyEvent(CompilerContext, SourceGraph, GetPressedPin(), IE_Pressed);
	CreateInputKeyEvent(CompilerContext, SourceGraph, GetReleasedPin(), IE_Released);
}

void UK2Node_InputKey::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	TArray<FKey> AllKeys;
	EKeys::GetAllKeys(AllKeys);

	auto CustomizeInputNodeLambda = [](UEdGraphNode* NewNode, bool bIsTemplateNode, FKey Key)
	{
		UK2Node_InputKey* InputNode = CastChecked<UK2Node_InputKey>(NewNode);
		InputNode->InputKey = Key;
	};

	// actions get registered under specific object-keys; the idea is that 
	// actions might have to be updated (or deleted) if their object-key is  
	// mutated (or removed)... here we use the node's class (so if the node 
	// type disappears, then the action should go with it)
	UClass* ActionKey = GetClass();

	for (FKey const Key : AllKeys)
	{
		// these will be handled by UK2Node_GetInputAxisKeyValue and UK2Node_GetInputVectorAxisValue respectively
		if (!Key.IsBindableInBlueprints() || Key.IsFloatAxis() || Key.IsVectorAxis())
		{
			continue;
		}

		// to keep from needlessly instantiating a UBlueprintNodeSpawner, first   
		// check to make sure that the registrar is looking for actions of this type
		// (could be regenerating actions for a specific asset, and therefore the 
		// registrar would only accept actions corresponding to that asset)
		if (!ActionRegistrar.IsOpenForRegistration(ActionKey))
		{
			continue;
		}

		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		NodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(CustomizeInputNodeLambda, Key);
		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UK2Node_InputKey::GetMenuCategory() const
{
	enum EAxisKeyCategory
	{
		GamepadKeyCategory,
		MouseButtonCategory,
		KeyEventCategory,
		AxisKeyCategory_MAX,
	};
	static FNodeTextCache CachedCategories[AxisKeyCategory_MAX];

	FText SubCategory;
	EAxisKeyCategory CategoryIndex = AxisKeyCategory_MAX;

	if (InputKey.IsGamepadKey())
	{
		SubCategory = LOCTEXT("GamepadCategory", "Gamepad Events");
		CategoryIndex = GamepadKeyCategory;
	}
	else if (InputKey.IsMouseButton())
	{
		SubCategory = LOCTEXT("MouseCategory", "Mouse Events");
		CategoryIndex = MouseButtonCategory;
	}
	else
	{
		SubCategory = LOCTEXT("KeyEventsCategory", "Key Events");
		CategoryIndex = KeyEventCategory;
	}

	if (CachedCategories[CategoryIndex].IsOutOfDate())
	{
		// FText::Format() is slow, so we cache this to save on performance
		CachedCategories[CategoryIndex] = FEditorCategoryUtils::BuildCategoryString(FCommonEditorCategory::Input, SubCategory);
	}
	return CachedCategories[CategoryIndex];
}

FBlueprintNodeSignature UK2Node_InputKey::GetSignature() const
{
	FBlueprintNodeSignature NodeSignature = Super::GetSignature();
	NodeSignature.AddKeyValue(InputKey.ToString());

	return NodeSignature;
}

#undef LOCTEXT_NAMESPACE
