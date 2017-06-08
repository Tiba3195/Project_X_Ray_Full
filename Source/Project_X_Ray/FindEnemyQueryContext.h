
#pragma once

#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BaseCharacter.h"
#include "TopdownCppPlayerController.h"
#include "FindEnemyQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API UFindEnemyQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:
		virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
	
};
