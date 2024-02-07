// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"


void USoundComponent::PlaySoundEffect()
{
    UAudioComponent* SelectedAudioComponent = AudioComponents[0];

    if (SelectedAudioComponent)
    {
        SelectedAudioComponent->Play();   
        //FVector SoundLocation = GetOwner()->GetActorLocation();
        //UGameplayStatics::PlaySoundAtLocation(GetWorld(), SelectedAudioComponent->Sound, SoundLocation);
    }
}
