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

FString UJsonParseLib::ReturnJsonParse(const FString& json)
{
	// �����⸦ �����
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);
	// �Ľ� ����� ���� ���� ����
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
	// �ؼ��� �Ѵ�.
	FString returnValue;
	if ( FJsonSerializer::Deserialize(reader , result) )
	{
		if ( result->HasField("message") ) {
			FString message = result->GetStringField("message");
			returnValue.Append(FString::Printf(TEXT("%s") , *message));
		}
	}
	// ��ȯ�Ѵ�.
	return returnValue;
}

FString UJsonParseLib::MakeLoginInfoJson(FString id , FString pwd)
{
	TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());
	jsonObject->SetStringField("identity" , *id);
	jsonObject->SetStringField("password" , *pwd);

	FString json;
	TSharedRef<TJsonWriter<TCHAR>> writer = TJsonWriterFactory<TCHAR>::Create(&json);
	FJsonSerializer::Serialize(jsonObject.ToSharedRef() , writer);

	return json;
}

FString UJsonParseLib::MakeSoundFileDate(FString user_id , FString song_id , FString track_id , float start_time , float end_time , FString audio_data)
{
	TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());

	jsonObject->SetStringField("user_id" , *user_id);
	jsonObject->SetStringField("song_id" , *song_id);
	jsonObject->SetStringField("track_id" , *track_id);
	jsonObject->SetNumberField("start_time" , start_time);
	jsonObject->SetNumberField("end_time" , end_time);
	jsonObject->SetStringField("audio_data" , *audio_data);

	FString json;
	TSharedRef<TJsonWriter<TCHAR>> writer = TJsonWriterFactory<TCHAR>::Create(&json);
	FJsonSerializer::Serialize(jsonObject.ToSharedRef() , writer);

	return json;
}

