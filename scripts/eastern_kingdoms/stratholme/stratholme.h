/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
* This program is free software licensed under GPL version 2
* Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_STRATHOLME_H
#define DEF_STRATHOLME_H

enum
{
    MAX_ENCOUNTER               = 8,
    MAX_SILVERHAND              = 5,
    MAX_ZIGGURATS               = 3,

    TYPE_BARON_RUN              = 0,
    TYPE_BARONESS               = 1,
    TYPE_NERUB                  = TYPE_BARONESS + 1,        // Assert that these three TYPEs are in correct order.
    TYPE_PALLID                 = TYPE_BARONESS + 2,
    TYPE_RAMSTEIN               = 4,
    TYPE_RAMSTEIN_OBSOLETE      = 5,                        // Still set in Acid, remove when removed from Acid :)
    TYPE_BARON                  = 6,                        // Adapt then
    TYPE_BARTHILAS_RUN          = 7,
    TYPE_BLACK_GUARDS           = 8,

    TYPE_SH_QUEST               = 20,
    TYPE_SH_CATHELA             = 21,
    TYPE_SH_GREGOR              = 22,
    TYPE_SH_NEMAS               = 23,
    TYPE_SH_VICAR               = 24,
    TYPE_SH_AELMAR              = 25,

    NPC_BARTHILAS               = 10435,
    NPC_BARONESS_ANASTARI       = 10436,
    NPC_NERUBENKAN              = 10437,
    NPC_MALEKI_THE_PALLID       = 10438,
    NPC_RAMSTEIN                = 10439,
    NPC_BARON                   = 10440,
    NPC_CRYSTAL                 = 10415,                    // three ziggurat crystals
    NPC_THUZADIN_ACOLYTE        = 10399,                    // acolytes in ziggurats
    NPC_ABOM_BILE               = 10416,
    NPC_ABOM_VENOM              = 10417,
    NPC_MINDLESS_UNDEAD         = 11030,                    // zombies summoned after ramstein
    NPC_BLACK_GUARD             = 10394,                    // zombies summoned after ramstein
    NPC_YSIDA                   = 16031,
    NPC_YSIDA_TRIGGER           = 16100,

    GO_SERVICE_ENTRANCE         = 175368,
    GO_GAUNTLET_GATE1           = 175357,
    GO_PORT_SLAUGHTER_GATE      = 175358,                   //port used at the undeads event
    GO_ZIGGURAT_DOOR_1          = 175380,                   //baroness
    GO_ZIGGURAT_DOOR_2          = 175379,                   //nerub'enkan
    GO_ZIGGURAT_DOOR_3          = 175381,                   //maleki
    GO_ZIGGURAT_DOOR_4          = 175405,                   //rammstein
    GO_ZIGGURAT_DOOR_5          = 175796,                   //baron
    GO_PORT_GAUNTLET            = 175374,                   //port from gauntlet to slaugther
    GO_PORT_SLAUGTHER           = 175373,                   //port at slaugther
    GO_PORT_ELDERS              = 175377,                   //port at elders square
    GO_YSIDA_CAGE               = 181071,                   // cage to open after baron event is done

    QUEST_DEAD_MAN_PLEA         = 8945,
    SPELL_BARON_ULTIMATUM       = 27861,

    SAY_ANNOUNCE_ZIGGURAT_1     = -1329004,
    SAY_ANNOUNCE_ZIGGURAT_2     = -1329005,
    SAY_ANNOUNCE_ZIGGURAT_3     = -1329006,
    SAY_ANNOUNCE_RIVENDARE      = -1329007,

    SAY_WARN_BARON              = -1329008,
    SAY_ANNOUNCE_RUN_START      = -1329009,
    SAY_ANNOUNCE_RUN_10_MIN     = -1329010,
    SAY_ANNOUNCE_RUN_5_MIN      = -1329011,
    SAY_ANNOUNCE_RUN_FAIL       = -1329012,
    SAY_ANNOUNCE_RAMSTEIN       = -1329013,
    SAY_UNDEAD_DEFEAT           = -1329014,
    SAY_EPILOGUE                = -1329015,
};

struct sEventLocation
{
    float m_fX, m_fY, m_fZ, m_fO;
};

static sEventLocation sStratholmeLocation[] =
{
    {3725.577f, -3599.484f, 142.367f},                      // barthilas door run
    {4068.284f, -3535.678f, 122.771f, 2.50f},               // barthilas tele
    {4032.643f, -3378.546f, 119.752f, 4.74f},               // ramstein summon loc
    {4032.843f, -3390.246f, 119.732f},                      // ramstein move loc
    {3969.357f, -3391.871f, 119.116f, 5.91f},               // skeletons summon loc
    {4033.044f, -3431.031f, 119.055f},                      // skeletons move loc
    {4032.602f, -3378.506f, 119.752f, 4.74f},               // guards summon loc
    {4042.575f, -3337.929f, 115.059f}                       // ysida move loc
};

struct ZigguratStore
{
    ObjectGuid m_doorGuid;
    ObjectGuid m_crystalGuid;
    GUIDList m_lZigguratAcolyteGuid;
};

class MANGOS_DLL_DECL instance_stratholme : public ScriptedInstance
{
    public:
        instance_stratholme(Map* pMap);
        ~instance_stratholme() {}

        void Initialize();

        void OnCreatureCreate(Creature* pCreature);
        void OnObjectCreate(GameObject* pGo);

        void SetData(uint32 uiType, uint32 uiData);
        uint32 GetData(uint32 uiType);

        const char* Save() { return m_strInstData.c_str(); }
        void Load(const char* chrIn);

        void OnCreatureEnterCombat(Creature* pCreature);
        void OnCreatureEvade(Creature* pCreature);
        void OnCreatureDeath(Creature* pCreature);

        void Update(uint32 uiDiff);

    protected:
        bool StartSlaugtherSquare();
        void DoSortZiggurats();
        void ThazudinAcolyteJustDied( Creature* pCreature );

        uint32 m_auiEncounter[MAX_ENCOUNTER];
        bool m_bIsSilverHandDead[MAX_SILVERHAND];
        std::string m_strInstData;

        uint32 m_uiBaronRunTimer;
        uint32 m_uiBarthilasRunTimer;
        uint32 m_uiMindlessSummonTimer;
        uint32 m_uiSlaugtherSquareTimer;

        uint32 m_uiYellCounter;
        uint32 m_uiMindlessCount;

        ZigguratStore m_zigguratStorage[MAX_ZIGGURATS];

        GUIDList m_luiCrystalGUIDs;
        GUIDSet m_sAbomnationGUID;
        GUIDList m_luiAcolyteGUIDs;
        GUIDList m_luiUndeadGUIDs;
        GUIDList m_luiGuardGUIDs;
};

#endif
