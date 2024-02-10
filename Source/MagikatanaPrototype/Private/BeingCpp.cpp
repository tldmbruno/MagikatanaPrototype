// Fill out your copyright notice in the Description page of Project Settings.


#include "BeingCpp.h"

// Sets default values
ABeingCpp::ABeingCpp()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool ABeingCpp::CalculateIsUnderShadow()
{
	UWorld* world = GetWorld();

	FVector currentLocation = GetActorLocation();
	FVector sunLocation = currentLocation + FVector(-10000, 0, 10000);

	FHitResult OutHit;

	bool didTraceHit = world->LineTraceSingleByChannel(OutHit, currentLocation, sunLocation, ECollisionChannel::ECC_Visibility);

	// Only apply major changes when the actor gets in or out of the shadow
	if (bIsUnderShadow != didTraceHit) {
		bIsUnderShadow = didTraceHit;
		UpdateMaterialsShadowVFX(ActorUnlitMeshes, bIsUnderShadow);
	}

	return bIsUnderShadow;
}

void ABeingCpp::UpdateMaterialsShadowVFX(TArray<UMeshComponent*> ShadedMeshes, bool bIsShaded)
{
	float shadowThresholdParameterValue = bIsShaded ? -1 : 0.3;
	float highlightThresholdParameterValue = bIsShaded ? 1 : 0.9;

	for (UMeshComponent* shadedMesh : ShadedMeshes)
	{
		shadedMesh->SetScalarParameterValueOnMaterials(FName("ShadowThreshold"), shadowThresholdParameterValue);
		shadedMesh->SetScalarParameterValueOnMaterials(FName("HighlightThreshold"), highlightThresholdParameterValue);
	}
}

void ABeingCpp::DisableAllMarkConditionVisualEffects(TArray<UMeshComponent*> ShadedMeshes)
{
	float disabledValue = 0;

	for (UMeshComponent* shadedMesh : ShadedMeshes)
	{
		if (shadedMesh == NULL) continue;

		shadedMesh->SetScalarParameterValueOnMaterials(FName("EnableMarkVFX"), disabledValue);
		shadedMesh->SetScalarParameterValueOnMaterials(FName("EnableMarkActivationVFX"), disabledValue);
	}
}

void ABeingCpp::SetScalarParameterValueOnMaterialsArray(TArray<UMeshComponent*> ShadedMeshes, FName ParameterName, float value)
{
	for (UMeshComponent* shadedMesh : ShadedMeshes)
	{
		if (shadedMesh == NULL) continue;

		shadedMesh->SetScalarParameterValueOnMaterials(ParameterName, value);
	}
}

// Called when the game starts or when spawned
void ABeingCpp::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABeingCpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABeingCpp::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

