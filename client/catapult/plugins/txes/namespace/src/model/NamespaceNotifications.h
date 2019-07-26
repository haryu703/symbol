/**
*** Copyright (c) 2016-present,
*** Jaguar0625, gimre, BloodyRookie, Tech Bureau, Corp. All rights reserved.
***
*** This file is part of Catapult.
***
*** Catapult is free software: you can redistribute it and/or modify
*** it under the terms of the GNU Lesser General Public License as published by
*** the Free Software Foundation, either version 3 of the License, or
*** (at your option) any later version.
***
*** Catapult is distributed in the hope that it will be useful,
*** but WITHOUT ANY WARRANTY; without even the implied warranty of
*** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*** GNU Lesser General Public License for more details.
***
*** You should have received a copy of the GNU Lesser General Public License
*** along with Catapult. If not, see <http://www.gnu.org/licenses/>.
**/

#pragma once
#include "NamespaceConstants.h"
#include "NamespaceTypes.h"
#include "catapult/model/Notifications.h"

namespace catapult { namespace model {

	// region namespace notification types

/// Defines a namespace notification type with \a DESCRIPTION, \a CODE and \a CHANNEL.
#define DEFINE_NAMESPACE_NOTIFICATION(DESCRIPTION, CODE, CHANNEL) DEFINE_NOTIFICATION_TYPE(CHANNEL, Namespace, DESCRIPTION, CODE)

	/// Namespace name was provided.
	DEFINE_NAMESPACE_NOTIFICATION(Name, 0x0001, Validator);

	/// Namespace was registered.
	DEFINE_NAMESPACE_NOTIFICATION(Registration, 0x0002, Validator);

	/// Root namespace was registered.
	DEFINE_NAMESPACE_NOTIFICATION(Root_Registration, 0x0003, All);

	/// Child namespace was registered.
	DEFINE_NAMESPACE_NOTIFICATION(Child_Registration, 0x0004, All);

	/// Namespace rental fee has been sent.
	DEFINE_NAMESPACE_NOTIFICATION(Rental_Fee, 0x0005, Observer);

	/// Namespace is required.
	DEFINE_NAMESPACE_NOTIFICATION(Required, 0x0006, Validator);

#undef DEFINE_NAMESPACE_NOTIFICATION

	// endregion

	// region NamespaceNameNotification

	/// Notification of a namespace name.
	struct NamespaceNameNotification : public Notification {
	public:
		/// Matching notification type.
		static constexpr auto Notification_Type = Namespace_Name_Notification;

	public:
		/// Creates a notification around \a nameSize and \a pName given \a namespaceId and \a parentId.
		NamespaceNameNotification(
				catapult::NamespaceId namespaceId,
				catapult::NamespaceId parentId,
				uint8_t nameSize,
				const uint8_t* pName)
				: Notification(Notification_Type, sizeof(NamespaceNameNotification))
				, NamespaceId(namespaceId)
				, ParentId(parentId)
				, NameSize(nameSize)
				, NamePtr(pName)
		{}

	public:
		/// Id of the namespace.
		catapult::NamespaceId NamespaceId;

		/// Id of the parent namespace.
		catapult::NamespaceId ParentId;

		/// Size of the name.
		uint8_t NameSize;

		/// Const pointer to the namespace name.
		const uint8_t* NamePtr;
	};

	// endregion

	// region NamespaceNotification

	/// Notification of a namespace registration.
	struct NamespaceNotification : public Notification {
	public:
		/// Matching notification type.
		static constexpr auto Notification_Type = Namespace_Registration_Notification;

	public:
		/// Creates a notification around \a namespaceType.
		explicit NamespaceNotification(model::NamespaceType namespaceType)
				: Notification(Notification_Type, sizeof(NamespaceNotification))
				, NamespaceType(namespaceType)
		{}

	public:
		/// Type of the registered namespace.
		model::NamespaceType NamespaceType;
	};

	// endregion

	// region RootNamespaceNotification

	/// Notification of a root namespace registration.
	struct RootNamespaceNotification : public Notification {
	public:
		/// Matching notification type.
		static constexpr auto Notification_Type = Namespace_Root_Registration_Notification;

	public:
		/// Creates a notification around \a signer, \a namespaceId and \a duration.
		RootNamespaceNotification(const Key& signer, NamespaceId namespaceId, BlockDuration duration)
				: Notification(Notification_Type, sizeof(RootNamespaceNotification))
				, Signer(signer)
				, NamespaceId(namespaceId)
				, Duration(duration)
		{}

	public:
		/// Signer.
		const Key& Signer;

		/// Id of the namespace.
		catapult::NamespaceId NamespaceId;

		/// Number of blocks for which the namespace should be valid.
		BlockDuration Duration;
	};

	// endregion

	// region ChildNamespaceNotification

	/// Notification of a child namespace registration.
	struct ChildNamespaceNotification : public Notification {
	public:
		/// Matching notification type.
		static constexpr auto Notification_Type = Namespace_Child_Registration_Notification;

	public:
		/// Creates a notification around \a signer, \a namespaceId and \a parentId.
		ChildNamespaceNotification(const Key& signer, NamespaceId namespaceId, NamespaceId parentId)
				: Notification(Notification_Type, sizeof(ChildNamespaceNotification))
				, Signer(signer)
				, NamespaceId(namespaceId)
				, ParentId(parentId)
		{}

	public:
		/// Signer.
		const Key& Signer;

		/// Id of the namespace.
		catapult::NamespaceId NamespaceId;

		/// Id of the parent namespace.
		catapult::NamespaceId ParentId;
	};

	// endregion

	// region NamespaceRentalFeeNotification

	/// Notification of a namespace rental fee.
	struct NamespaceRentalFeeNotification : public BasicBalanceNotification<NamespaceRentalFeeNotification> {
	public:
		/// Matching notification type.
		static constexpr auto Notification_Type = Namespace_Rental_Fee_Notification;

	public:
		/// Creates a notification around \a sender, \a recipient, \a mosaicId and \a amount.
		NamespaceRentalFeeNotification(
				const Key& sender,
				const UnresolvedAddress& recipient,
				UnresolvedMosaicId mosaicId,
				catapult::Amount amount)
				: BasicBalanceNotification(sender, mosaicId, amount)
				, Recipient(recipient)
		{}

	public:
		/// Recipient.
		UnresolvedAddress Recipient;
	};

	// endregion

	// region namespace required

	/// Notification of a required namespace.
	struct NamespaceRequiredNotification : public Notification {
	public:
		/// Matching notification type.
		static constexpr auto Notification_Type = Namespace_Required_Notification;

	public:
		/// Creates a notification around \a signer and \a namespaceId.
		NamespaceRequiredNotification(const Key& signer, NamespaceId namespaceId)
				: Notification(Notification_Type, sizeof(NamespaceRequiredNotification))
				, Signer(signer)
				, NamespaceId(namespaceId)
		{}

	public:
		/// Signer.
		const Key& Signer;

		/// Namespace id.
		catapult::NamespaceId NamespaceId;
	};

	// endregion
}}
