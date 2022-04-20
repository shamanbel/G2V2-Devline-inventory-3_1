// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"


class G2VS2_API FEnvironmentDelegates
{
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDayTimeChanged, const FGameplayTag&);
	static FOnDayTimeChanged OnDayTimeChanged;
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDateTimeUpdated, const FTimespan&);
	static FOnDateTimeUpdated OnDateTimeUpdated;
};
