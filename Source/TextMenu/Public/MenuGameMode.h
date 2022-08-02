// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainBaseGameMode.h"
#include "Blueprint/UserWidget.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TEXTMENU_API AMenuGameMode : public AMainBaseGameMode
{
	GENERATED_BODY()
public:
	/** �Ƴ���ǰ�˵��ؼ�������ָ���ࣨ���У����½��ؼ���*/
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	/** ��Ϸ��ʼʱ���á�*/
	virtual void BeginPlay() override;

	/** ��Ϸ��ʼʱ�������˵��Ŀؼ��ࡣ*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	/** �����˵��Ŀؼ�ʵ����*/
	UPROPERTY()
		UUserWidget* CurrentWidget;
};
