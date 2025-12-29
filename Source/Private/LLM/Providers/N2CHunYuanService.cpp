// Fill out your copyright notice in the Description page of Project Settings.


#include "LLM/Providers/N2CHunYuanService.h"

#include "Utils/N2CLogger.h"

class UN2CSettings;

void UN2CHunYuanService::GetConfiguration(FString& OutEndpoint, FString& OutAuthToken, bool& OutSupportsSystemPrompts)
{
	OutEndpoint = GetDefaultEndpoint();
	OutAuthToken = Config.ApiKey;
	OutSupportsSystemPrompts = false;
}

FString UN2CHunYuanService::GetDefaultEndpoint() const
{
	return TEXT("https://api.hunyuan.cloud.tencent.com/v1/chat/completions");
}

FString UN2CHunYuanService::FormatRequestPayload(const FString& UserMessage, const FString& SystemMessage) const
{
	// Load settings
	const UN2CSettings* Settings = GetDefault<UN2CSettings>();
	if (!Settings)
	{
		FN2CLogger::Get().LogError(TEXT("Failed to load plugin settings"), TEXT("LLMModule"));
	}

	// Create and configure payload builder
	UN2CLLMPayloadBuilder* PayloadBuilder = NewObject<UN2CLLMPayloadBuilder>();
	PayloadBuilder->Initialize(Config.Model);
	PayloadBuilder->ConfigureForDeepSeek();
    
	// Set common parameters
	PayloadBuilder->SetTemperature(0.0f);
	PayloadBuilder->SetMaxTokens(8000);
    
	// Try prepending source files to the user message
	FString FinalUserMessage = UserMessage;
    
	// Add messages
	PayloadBuilder->AddSystemMessage(SystemMessage);
	PayloadBuilder->AddUserMessage(FinalUserMessage);
	
    
	// Build and return the payload
	return PayloadBuilder->Build();
}

