// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MagiBeing.generated.h"

UCLASS()
class MAGIKATANAPROTOTYPE_API AMagiBeing : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMagiBeing();

	UPROPERTY(BlueprintReadWrite)
	bool bIsUnderShadow;

	UPROPERTY(BlueprintReadWrite)
	TArray<UMeshComponent*> ActorUnlitMeshes;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	bool CalculateIsUnderShadow();

	/**
	* Enables/Disables the effect of being completely obscured by shadows, if the material has the proper parameters.
	* @param ShadedMeshes All the meshes that will be affected by the shadow/sun.
	* @param IsShaded Are the meshes under the shadows?
	*/
	UFUNCTION(BlueprintCallable)
	void UpdateMaterialsShadowVFX(TArray<UMeshComponent*> ShadedMeshes, bool IsShaded);

	UFUNCTION(BlueprintCallable)
	void DisableAllMarkConditionVisualEffects(TArray<UMeshComponent*> ShadedMeshes);

	/**
	* Same as SetScalarParameterValueOnMaterials, but set an entire array of meshes at once.
	* @param ShadedMeshes All the meshes that will be affected by the shadow/sun.
	* @param ParameterName Name of the parameter that will be changed.
	* @param Value Value that the Parameter will be set to.
	*/
	UFUNCTION(BlueprintCallable)
	void SetScalarParameterValueOnMaterialsArray(TArray<UMeshComponent*> ShadedMeshes, FName ParameterName, float Value);
};
