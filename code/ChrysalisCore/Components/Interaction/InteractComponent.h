#pragma once

#include <Components/Interaction/EntityInteractionComponent.h>
#include <Actor/Animation/Actions/ActorAnimationActionInteration.h>


namespace Chrysalis
{
class CInteractComponent
	: public IEntityComponent
	, public IInteractionInteract
	, public IAnimationEventListener
{
protected:
	friend CChrysalisCorePlugin;
	static void Register(Schematyc::CEnvRegistrationScope& componentScope);

	// IEntityComponent
	virtual void Initialize() final;
	// ~IEntityComponent

public:
	CInteractComponent() {}
	virtual ~CInteractComponent() {}

	static void ReflectType(Schematyc::CTypeDesc<CInteractComponent>& desc);

	static CryGUID& IID()
	{
		static CryGUID id = "{C03D46F4-D1C9-45BE-AAC6-2362EFD3ABCC}"_cry_guid;
		return id;
	}

	const string kQueueSignal { "interaction_interact" };
	const string kInteractStartVerb { "interaction_interact_start" };
	const string kInteractTickVerb { "interaction_interact_tick" };
	const string kInteractCompleteVerb { "interaction_interact_complete" };
	const string kInteractCancelVerb { "interaction_interact_cancel" };

	const string kInteractAnimationEnterVerb { "interaction_animation_enter" };
	const string kInteractAnimationFailVerb { "interaction_animation_fail" };
	const string kInteractAnimationExitVerb { "interaction_animation_exit" };

	struct SInteractStartSignal
	{
		SInteractStartSignal() = default;
	};


	struct SInteractTickSignal
	{
		SInteractTickSignal() = default;
		SInteractTickSignal(float deltaPitch, float deltaYaw) : m_deltaPitch (deltaPitch), m_deltaYaw(deltaYaw) {}

		float m_deltaPitch { 0.0f };
		float m_deltaYaw { 0.0f };
	};


	struct SInteractCompleteSignal
	{
		SInteractCompleteSignal() = default;
	};


	struct SInteractCancelSignal
	{
		SInteractCancelSignal() = default;
	};


	struct SInteractAnimationEnterSignal
	{
		SInteractAnimationEnterSignal() = default;
	};


	struct SInteractAnimationFailSignal
	{
		SInteractAnimationFailSignal() = default;
	};


	struct SInteractAnimationExitSignal
	{
		SInteractAnimationExitSignal() = default;
	};


	struct SInteractAnimationEventSignal
	{
		SInteractAnimationEventSignal() = default;
		SInteractAnimationEventSignal(Schematyc::CSharedString eventName,
			uint32 eventNameLowercaseCRC32,
			Schematyc::CSharedString customParameter,
			float time, float endTime,
			Schematyc::CSharedString bonePathName,
			Vec3 boneDirection,
			Vec3 boneOffset)
			: m_eventName(eventName), 
			m_eventNameLowercaseCRC32(eventNameLowercaseCRC32),
			m_customParameter(customParameter),
			m_time(time), m_endTime(endTime),
			m_bonePathName(bonePathName),
			m_boneDirection(boneDirection),
			m_boneOffset(boneOffset)
		{}

		Schematyc::CSharedString m_eventName { "" };
		uint32 m_eventNameLowercaseCRC32 { 0 };
		Schematyc::CSharedString m_customParameter { "" };
		float m_time { 0.0f };
		float m_endTime { 0.0f };
		Schematyc::CSharedString m_bonePathName { "" };
		Vec3 m_boneDirection { Vec3(ZERO) };
		Vec3 m_boneOffset { Vec3(ZERO) };
	};


	// IInteractionInteract
	virtual void OnInteractionInteractStart(IActorComponent& actor) override;
	virtual void OnInteractionInteractTick(IActorComponent& actor) override;
	virtual void OnInteractionInteractComplete(IActorComponent& actor) override;
	virtual void OnInteractionInteractCancel(IActorComponent& actor) override;
	// ~IInteractionInteract

	// IAnimationEventListener
	virtual void OnActionAnimationEnter() override;
	virtual void OnActionAnimationFail(EActionFailure actionFailure) override;
	virtual void OnActionAnimationExit() override;
	virtual void OnActionAnimationEvent(ICharacterInstance* pCharacter, const AnimEventInstance& event) override;
	// ~IAnimationEventListener

protected:
	void InformAllLinkedEntities(string verb, bool isInteractedOn);

	virtual void OnResetState();

	/** True if this Interact is able to be used. */
	bool m_isEnabled { true };

	/** True if this Interact can only be used once. */
	bool m_isSingleUseOnly { false };

	/** Keep track of these so we can enable / disable as needed. */
	CInteractionInteractPtr m_interactPtr { nullptr };

	/** This entity should be interactive. */
	CEntityInteractionComponent* m_interactor { nullptr };

	/** Send an alternative queue signal to DRS if the string is not empty. */
	Schematyc::CSharedString m_queueSignal;

	/** During the processing cycle for an interaction, this will hold the actor that initiated the interaction. It will
	be invalid at all other times. */
	IActorComponent* m_pInteractionActor { nullptr };
};
}