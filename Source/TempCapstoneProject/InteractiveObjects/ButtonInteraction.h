// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../InteractionInterface.h"
#include "ButtonInteraction.generated.h"

UCLASS()
class TEMPCAPSTONEPROJECT_API AButtonInteraction : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonInteraction();

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Interactive Object")
	AActor* TargetActor;

	UPROPERTY(Replicated)
	bool bIsActive = false;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive Object")
	class USkeletalMeshComponent* ObjectMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Interface Functions
	virtual void Interact() override;

	UFUNCTION(NetMulticast, Reliable)
	void NMC_Interact();

	virtual void ShowInteractionWidget() override;
	virtual void HideInteractionWidget() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ReceiveInteract"))
	void ReceiveInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsActive() { return bIsActive; };

private:
	UPROPERTY(EditAnywhere)
	class USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, Category = "Interactive Object")
	class UBoxComponent* ButtonCollider;

	UPROPERTY(EditAnywhere, Category = "Interactive Object")
	class UWidgetComponent* InteractionWidget;
};
