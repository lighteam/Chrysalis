#pragma once

#include "ICryMannequin.h"
#include "Actor/Animation/ActorAnimation.h"
#include "Utility/Listener.h"


namespace Chrysalis
{
class CActorAnimationActionInteraction : public CAnimationAction
{
public:
	DEFINE_ACTION("Interaction");

	CActorAnimationActionInteraction();
	virtual ~CActorAnimationActionInteraction() {};

	/** Listen for animation events that are triggered while running this action. */
	struct IAnimationEventListener
	{
		virtual ~IAnimationEventListener() {};

		virtual void OnActionAnimationEvent() = 0;
	};

	// IAction
	void OnInitialise() override;
	void Enter() override;
	void Fail(EActionFailure actionFailure) override;
	void Exit() override;
	IAction::EStatus UpdatePending(float timePassed) override;
	IAction::EStatus Update(float timePassed) override;
	void Install() override;
	virtual void OnAnimationEvent(ICharacterInstance* pCharacter, const AnimEventInstance& event) override;
	// ~IAction

private:
	const struct SMannequinInteractionParams* m_interactionParams;

	/** Listeners for animation events. */
	TListener<IAnimationEventListener> m_listenersAnimationEvents;
};
}