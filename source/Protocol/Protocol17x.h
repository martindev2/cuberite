
// Protocol17x.h

/*
Declares the 1.7.x protocol classes:
	- cProtocol172
		- release 1.7.2 protocol (#4)
(others may be added later in the future for the 1.7 release series)
*/





#pragma once

#include "Protocol.h"
#include "../ByteBuffer.h"
#include "../../CryptoPP/modes.h"
#include "../../CryptoPP/aes.h"





class cProtocol172 :
	public cProtocol  // TODO
{
	typedef cProtocol super;  // TODO
	
public:

	cProtocol172(cClientHandle * a_Client, const AString & a_ServerAddress, UInt16 a_ServerPort, UInt32 a_State);
	
	/// Called when client sends some data:
	virtual void DataReceived(const char * a_Data, int a_Size) override;

	/// Sending stuff to clients (alphabetically sorted):
	virtual void SendAttachEntity        (const cEntity & a_Entity, const cEntity * a_Vehicle) override;
	virtual void SendBlockAction         (int a_BlockX, int a_BlockY, int a_BlockZ, char a_Byte1, char a_Byte2, BLOCKTYPE a_BlockType) override;
	virtual void SendBlockBreakAnim	     (int a_EntityID, int a_BlockX, int a_BlockY, int a_BlockZ, char a_Stage) override;
	virtual void SendBlockChange         (int a_BlockX, int a_BlockY, int a_BlockZ, BLOCKTYPE a_BlockType, NIBBLETYPE a_BlockMeta) override;
	virtual void SendBlockChanges        (int a_ChunkX, int a_ChunkZ, const sSetBlockVector & a_Changes) override;
	virtual void SendChat                (const AString & a_Message) override;
	virtual void SendChunkData           (int a_ChunkX, int a_ChunkZ, cChunkDataSerializer & a_Serializer) override;
	virtual void SendCollectPickup       (const cPickup & a_Pickup, const cPlayer & a_Player) override;
	virtual void SendDestroyEntity       (const cEntity & a_Entity) override;
	virtual void SendDisconnect          (const AString & a_Reason) override;
	virtual void SendEditSign            (int a_BlockX, int a_BlockY, int a_BlockZ) override;  ///< Request the client to open up the sign editor for the sign (1.6+)
	virtual void SendEntityEquipment     (const cEntity & a_Entity, short a_SlotNum, const cItem & a_Item) override;
	virtual void SendEntityHeadLook      (const cEntity & a_Entity) override;
	virtual void SendEntityLook          (const cEntity & a_Entity) override;
	virtual void SendEntityMetadata      (const cEntity & a_Entity) override;
	virtual void SendEntityProperties    (const cEntity & a_Entity) override;
	virtual void SendEntityRelMove       (const cEntity & a_Entity, char a_RelX, char a_RelY, char a_RelZ) override;
	virtual void SendEntityRelMoveLook   (const cEntity & a_Entity, char a_RelX, char a_RelY, char a_RelZ) override;
	virtual void SendEntityStatus        (const cEntity & a_Entity, char a_Status) override;
	virtual void SendEntityVelocity      (const cEntity & a_Entity) override;
	virtual void SendExplosion           (double a_BlockX, double a_BlockY, double a_BlockZ, float a_Radius, const cVector3iArray & a_BlocksAffected, const Vector3d & a_PlayerMotion) override;
	virtual void SendGameMode            (eGameMode a_GameMode) override;
	virtual void SendHealth              (void) override;
	virtual void SendInventorySlot       (char a_WindowID, short a_SlotNum, const cItem & a_Item) override;
	virtual void SendKeepAlive           (int a_PingID) override;
	virtual void SendLogin               (const cPlayer & a_Player, const cWorld & a_World) override;
	virtual void SendPickupSpawn         (const cPickup & a_Pickup) override;
	virtual void SendPlayerAbilities     (void) override;
	virtual void SendPlayerAnimation     (const cPlayer & a_Player, char a_Animation) override;
	virtual void SendPlayerListItem      (const cPlayer & a_Player, bool a_IsOnline) override;
	virtual void SendPlayerMaxSpeed      (void) override;
	virtual void SendPlayerMoveLook      (void) override;
	virtual void SendPlayerPosition      (void) override;
	virtual void SendPlayerSpawn         (const cPlayer & a_Player) override;
	virtual void SendRespawn             (void) override;
	virtual void SendSoundEffect         (const AString & a_SoundName, int a_SrcX, int a_SrcY, int a_SrcZ, float a_Volume, float a_Pitch) override;  // a_Src coords are Block * 8
	virtual void SendSoundParticleEffect (int a_EffectID, int a_SrcX, int a_SrcY, int a_SrcZ, int a_Data) override;
	virtual void SendSpawnFallingBlock   (const cFallingBlock & a_FallingBlock) override;
	virtual void SendSpawnMob            (const cMonster & a_Mob) override;
	virtual void SendSpawnObject         (const cEntity & a_Entity, char a_ObjectType, int a_ObjectData, Byte a_Yaw, Byte a_Pitch) override;
	virtual void SendSpawnVehicle        (const cEntity & a_Vehicle, char a_VehicleType, char a_VehicleSubType) override;
	virtual void SendTabCompletionResults(const AStringVector & a_Results) override;
	virtual void SendTeleportEntity      (const cEntity & a_Entity) override;
	virtual void SendThunderbolt         (int a_BlockX, int a_BlockY, int a_BlockZ) override;
	virtual void SendTimeUpdate          (Int64 a_WorldAge, Int64 a_TimeOfDay) override;
	virtual void SendUnloadChunk         (int a_ChunkX, int a_ChunkZ) override;
	virtual void SendUpdateSign          (int a_BlockX, int a_BlockY, int a_BlockZ, const AString & a_Line1, const AString & a_Line2, const AString & a_Line3, const AString & a_Line4) override;
	virtual void SendUseBed              (const cEntity & a_Entity, int a_BlockX, int a_BlockY, int a_BlockZ ) override;
	virtual void SendWeather             (eWeather a_Weather) override;
	virtual void SendWholeInventory      (const cInventory & a_Inventory) override;
	virtual void SendWholeInventory      (const cWindow    & a_Window) override;
	virtual void SendWindowClose         (const cWindow    & a_Window) override;
	virtual void SendWindowOpen          (char a_WindowID, char a_WindowType, const AString & a_WindowTitle, char a_NumSlots) override;
	virtual void SendWindowProperty      (const cWindow & a_Window, short a_Property, short a_Value) override;

	virtual AString GetAuthServerID(void) override { return m_AuthServerID; }

protected:

	AString m_ServerAddress;
	
	UInt16 m_ServerPort;
	
	AString m_AuthServerID;
	
	/// State of the protocol. 1 = status, 2 = login, 3 = game
	UInt32 m_State;

	/// Buffer for the received data
	cByteBuffer m_ReceivedData;
	
	bool m_IsEncrypted;
	CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption m_Decryptor;
	CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption m_Encryptor;
	
	/// (Unencrypted) data to be sent to the client. Written by SendData, cleared by Flush()
	AString m_DataToSend;
	
	
	/// Adds the received (unencrypted) data to m_ReceivedData, parses complete packets
	void AddReceivedData(const char * a_Data, int a_Size);
	
	/// Reads and handles the packet. The packet length and type have already been read.
	void HandlePacket(UInt32 a_PacketType, UInt32 a_RemainingBytes);
	
	// Packet handlers while in the Status state (m_State == 1):
	void HandlePacketStatusPing   (UInt32 a_RemainingBytes);
	void HandlePacketStatusRequest(UInt32 a_RemainingBytes);
	
	// Packet handlers while in the Login state (m_State == 2):
	void HandlePacketLoginEncryptionResponse(UInt32 a_RemainingBytes);
	void HandlePacketLoginStart             (UInt32 a_RemainingBytes);
	
	// Packet handlers while in the Game state (m_State == 3):
	void HandlePacketAnimation              (UInt32 a_RemainingBytes);
	void HandlePacketBlockDig               (UInt32 a_RemainingBytes);
	void HandlePacketBlockPlace             (UInt32 a_RemainingBytes);
	void HandlePacketChatMessage            (UInt32 a_RemainingBytes);
	void HandlePacketClientSettings         (UInt32 a_RemainingBytes);
	void HandlePacketClientStatus           (UInt32 a_RemainingBytes);
	void HandlePacketCreativeInventoryAction(UInt32 a_RemainingBytes);
	void HandlePacketEntityAction           (UInt32 a_RemainingBytes);
	void HandlePacketKeepAlive              (UInt32 a_RemainingBytes);
	void HandlePacketPlayer                 (UInt32 a_RemainingBytes);
	void HandlePacketPlayerAbilities        (UInt32 a_RemainingBytes);
	void HandlePacketPlayerLook             (UInt32 a_RemainingBytes);
	void HandlePacketPlayerPos              (UInt32 a_RemainingBytes);
	void HandlePacketPlayerPosLook          (UInt32 a_RemainingBytes);
	void HandlePacketPluginMessage          (UInt32 a_RemainingBytes);
	void HandlePacketSlotSelect             (UInt32 a_RemainingBytes);
	void HandlePacketSteerVehicle           (UInt32 a_RemainingBytes);
	void HandlePacketTabComplete            (UInt32 a_RemainingBytes);
	void HandlePacketUpdateSign             (UInt32 a_RemainingBytes);
	void HandlePacketUseEntity              (UInt32 a_RemainingBytes);
	void HandlePacketWindowClick            (UInt32 a_RemainingBytes);
	void HandlePacketWindowClose            (UInt32 a_RemainingBytes);
	
	
	/// Writes an entire packet into the output stream. a_Packet is expected to start with the packet type; data length is prepended here.
	void WritePacket(cByteBuffer & a_Packet);

	/// Adds unencrypted data to the outgoing data buffer
	virtual void SendData(const char * a_Data, int a_Size) override;

	/// Flushes m_DataToSend through the optional encryption into the outgoing socket data
	virtual void Flush(void) override;
	
	void SendCompass(const cWorld & a_World);
} ;




