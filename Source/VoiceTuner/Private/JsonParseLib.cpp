// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonParseLib.h"

FString UJsonParseLib::TokenJsonParse(const FString& json)
{
	// �����⸦ �����
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);
	// �Ľ� ����� ���� ���� ����
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
	// �ؼ��� �Ѵ�.
	FString returnValue;
	if ( FJsonSerializer::Deserialize(reader , result) )
	{
		if ( result->HasField("token") ) {
			FString token = result->GetStringField("token");
			returnValue.Append(FString::Printf(TEXT("%s") , *token));
		}
	}
	// ��ȯ�Ѵ�.
	return returnValue;
}