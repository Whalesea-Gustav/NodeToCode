// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LLM/N2CBaseLLMService.h"
#include "N2CHunYuanService.generated.h"

/**
 * 
 */
UCLASS()
class NODETOCODE_API UN2CHunYuanService : public UN2CBaseLLMService
{
	GENERATED_BODY()
	
public:
	virtual  void GetConfiguration(FString& OutEndpoint, FString& OutAuthToken, bool& OutSupportsSystemPrompts) override;
	
private:
	virtual FString GetDefaultEndpoint() const override;
	
	virtual FString FormatRequestPayload(const FString& UserMessage, const FString& SystemMessage) const override;
};
