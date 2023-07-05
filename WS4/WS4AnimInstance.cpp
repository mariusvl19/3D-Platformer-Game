// Marius Vlad


#include "WS4AnimInstance.h"
#include "WS4Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWS4AnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (WS4Character == nullptr)
	{
		WS4Character = Cast<AWS4Character>(TryGetPawnOwner());
	}

	if (WS4Character)
	{
		//Get the lateral speed of the character from velocity
		FVector velocity{ WS4Character->GetVelocity() };
		velocity.Z = 0;
		speed = velocity.Size();

		//Checks if the character is in the air
		bIsInAir = WS4Character->GetCharacterMovement()->IsFalling();

		//Checks if the character is moving
		if (WS4Character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelarating = true;
		}
		else
		{
			bIsAccelarating = false;
		}
	}
}

void UWS4AnimInstance::NativeInitializeAnimation()
{
	WS4Character = Cast<AWS4Character>(TryGetPawnOwner());
}
