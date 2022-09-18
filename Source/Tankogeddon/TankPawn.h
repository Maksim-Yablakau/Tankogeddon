#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
UCLASS()
class TANKOGEDDON_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	ATankPawn();

	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Componets")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Componets")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Componets")
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Componets")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Componets")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementSpeed = 100.0f;

private:
	float ForwardMoveAxisValue = 0.0f;
	float RightMoveAxisValue = 0.0f;
};