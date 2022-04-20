// Fill out your copyright notice in the Description page of Project Settings.


#include "DateTimeSystemSettings.h"

UDateTimeSystemSettings::UDateTimeSystemSettings()
{
	InitialDateTime = FTimespan(1, 9, 0, 0);
	TimeRate = 1000.f;
}
