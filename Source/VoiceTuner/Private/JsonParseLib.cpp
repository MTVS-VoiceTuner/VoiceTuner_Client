// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonParseLib.h"

FString UJsonParseLib::TokenJsonParse(const FString& json)
{
	// 리더기를 만들고
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);
	// 파싱 결과를 담을 변수 선언
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
	// 해석을 한다.
	FString returnValue;
	FString token;
	if ( FJsonSerializer::Deserialize(reader , result) )
	{
		TSharedPtr<FJsonObject> JsonObj;
		if ( result->HasField("response") ) {
			JsonObj = result->GetObjectField("response");
			if ( JsonObj->HasField("accessToken") )
				token = JsonObj->GetStringField("accessToken");
		}
	}
	// 반환한다.
	return token;
}

FString UJsonParseLib::ReturnJsonParse(const FString& json)
{

	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);

	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	FString returnValue;
	if ( FJsonSerializer::Deserialize(reader , result) )
	{
		if ( result->HasField("message") ) {
			FString message = result->GetStringField("message");
			returnValue.Append(FString::Printf(TEXT("%s") , *message));
		}
	}
	return returnValue;
}

FString UJsonParseLib::MakeLoginInfoJson(FString id , FString pwd)
{
	TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());
	jsonObject->SetStringField("email" , *id);
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

FString UJsonParseLib::MakeUserInfoJson(const TMap<FString, FString> source)
{
	TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());
	TSharedPtr<FJsonObject> Temp = MakeShareable(new FJsonObject());

	for ( TPair<FString , FString> pair : source )
	{
		Temp->SetStringField(pair.Key , pair.Value);
	}

	TArray<TSharedPtr<FJsonValue>> JsonArray;
	JsonArray.Add(MakeShareable(new FJsonValueObject(Temp)));
	jsonObject->SetArrayField(FString::Printf(TEXT("userInfo")) , JsonArray);

	FString json;
	TSharedRef<TJsonWriter<TCHAR>> writer = TJsonWriterFactory<TCHAR>::Create(&json);
	FJsonSerializer::Serialize(jsonObject.ToSharedRef() , writer);

	return json;
}

