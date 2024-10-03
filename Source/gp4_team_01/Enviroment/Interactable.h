#pragma once

class GP4_TEAM_01_API IInteractable {
public:
	virtual ~IInteractable() = default;

public:
	virtual void Interact(AActor* Caller) = 0;
	virtual void Break() { bIsBroken = true; } ;

protected:
	bool bIsBroken = false;
};
