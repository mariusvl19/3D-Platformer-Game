// Marius Vlad

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WS4AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WS4_API UWS4AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	virtual void NativeInitializeAnimation() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category  = Movement, meta = (AllowPrivateAccess = "true"))
	class AWS4Character* WS4Character;

	//The speed of the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category  = Movement, meta = (AllowPrivateAccess = "true"))
	float speed;

	//A variable to checks if the character is in the air
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	//A variable to checks if the character is moving
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsAccelarating;
};
