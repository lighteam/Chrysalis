#include <StdAfx.h>

#include "ActorAnimationActionInteration.h"
#include <Actor/ActorComponent.h>


namespace Chrysalis
{
#define INTERACTION_FRAGMENTS( x ) \
	x( Interaction ) \

#define INTERACTION_TAGS( x ) \
	x( InteractionHigh ) /* The general height of the interaction object. */ \
	x( InteractionMiddle ) \
	x( InteractionLow ) \
	x( InteractionGrabObject ) /*  */ \
	x( InteractionFlipSwitch ) \
	x( InteractionDeadLift ) \
	x( InteractionTurnWheel ) \

#define INTERACTION_TAGGROUPS( x ) \
	x( InteractionHeight ) \
	x( InteractionMethod ) \

#define INTERACTION_SCOPES( x ) \

#define INTERACTION_CONTEXTS( x )

#define INTERACTION_FRAGMENT_TAGS( x )

MANNEQUIN_USER_PARAMS(SMannequinInteractionParams, INTERACTION_FRAGMENTS, INTERACTION_TAGS, INTERACTION_TAGGROUPS, INTERACTION_SCOPES, INTERACTION_CONTEXTS, INTERACTION_FRAGMENT_TAGS);


CActorAnimationActionInteraction::CActorAnimationActionInteraction()
	: CAnimationAction(EActorActionPriority::eAAP_Interaction, FRAGMENT_ID_INVALID, TAG_STATE_EMPTY, IAction::FragmentIsOneShot)
{
}


void CActorAnimationActionInteraction::OnInitialise()
{
	CAnimationAction::OnInitialise();

	m_interactionParams = GetMannequinUserParams<SMannequinInteractionParams>(*m_context);
	CRY_ASSERT(m_interactionParams);

	// Set the fragment for animation.
	SetFragment(m_interactionParams->fragmentIDs.Interaction);
}


void CActorAnimationActionInteraction::Install()
{
	CAnimationAction::Install();
}


void CActorAnimationActionInteraction::Enter()
{
	CAnimationAction::Enter();

	// Grab the actor in the root scope.
	CActorComponent& actor = *CActorComponent::GetActor(m_rootScope->GetEntityId());

	// Inform the actor we are taking control of an interation.
	actor.InteractionStart();

	// TEST!
	GetContext().state.Set(m_interactionParams->tagIDs.InteractionMiddle, true);
	GetContext().state.Set(m_interactionParams->tagIDs.InteractionGrabObject, true);
}


void CActorAnimationActionInteraction::Fail(EActionFailure actionFailure)
{
	CAnimationAction::Fail(actionFailure);
}


void CActorAnimationActionInteraction::Exit()
{
	CAnimationAction::Exit();

	// Grab the actor in the root scope.
	CActorComponent& actor = *CActorComponent::GetActor(m_rootScope->GetEntityId());

	// Inform the actor we are finished with an interation.
	actor.InteractionEnd();

	// TEST!
	GetContext().state.Set(m_interactionParams->tagIDs.InteractionMiddle, false);
	GetContext().state.Set(m_interactionParams->tagIDs.InteractionGrabObject, false);
}


IAction::EStatus CActorAnimationActionInteraction::UpdatePending(float timePassed)
{
	CAnimationAction::UpdatePending(timePassed);

	return EStatus();
}


IAction::EStatus CActorAnimationActionInteraction::Update(float timePassed)
{
	CAnimationAction::Update(timePassed);

	// Update the fragments and tags if they are different.
	if (m_rootScope->IsDifferent(m_fragmentID, m_fragTags))
		SetFragment(m_fragmentID, m_fragTags);

	return EStatus();
}
}