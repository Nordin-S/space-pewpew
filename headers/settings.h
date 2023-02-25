#ifndef METODIK_INVADERS2_SETTINGS_H
#define METODIK_INVADERS2_SETTINGS_H

#include <string>
#include <vector>
#include <QList>
#include <QString>
#include <map>
#include <QMap>

namespace space_pewpew {
  /**
   * @Author: Nordin Suleimani 14/2/2023
   * @file settings.h
   * @namespace settings
   * @brief The settings namespace contains all the settings and some utility functions.
   */
  namespace settings {
    /**
     * @Brief: GameStates enum contains the default game states.
     */
    enum GameState {
      MAIN_MENU,
      RUNNING,
      PAUSED,
      GAME_OVER
    };

    /**
     * @Brief: Healths enum contains the default health values for player, enemies types.
     */
    enum Healths {
      PlayerHealth = 100,
      FighterHealth = 30,
      BomberHealth = 150,
      BossHealth = 400
    };

    /**
     * @Brief: ShipSpeeds enum contains the default speed values for player, enemies types.
     */
    enum ShipSpeeds {
      PlayerSpeed = 18, FighterSpeed = 13, BomberSpeed = 6, BossSpeed = 2
    };

    /**
     * @Brief: UpdateMs enum contains the default update values.
     */
    enum UpdateMs {
      UMs01 = 1,
      UMs02 = 2,
      UMs03 = 3,
      UMs04 = 4,
      UMs05 = 5,
      UMs06 = 6,
      UMs07 = 7,
      UMs08 = 8,
      UMs09 = 9,
      UMs10 = 10,
      UMs15 = 15,
      UMs20 = 20,
      UMs25 = 25,
      UMs30 = 30,
      UMs35 = 35,
      UMs40 = 40,
      UMs45 = 45,
      UMs50 = 50,
      UMs60 = 60,
      UMs70 = 70,
      UMs80 = 80,
      UMs90 = 90,
      UMs100 = 100,
      UMs150 = 150,
      UMs200 = 200,
      UMs300 = 300,
      UMs400 = 400,
      UMs500 = 500,
      UMs600 = 600,
      UMs700 = 700,
      UMs800 = 800,
      UMs900 = 900,
      UMs1000 = 1000,
    };

    /**
     * @Brief: MoveSteps enum contains the default move steps values.
     */
    enum MoveSteps {
      Move01 = 1,
      Move02 = 2,
      Move03 = 3,
      Move04 = 4,
      Move05 = 5,
      Move06 = 6,
      Move07 = 7,
      Move08 = 8,
      Move09 = 9,
      Move10 = 10,
      Move11 = 11,
      Move12 = 12,
      Move13 = 13,
      Move14 = 14,
      Move15 = 15,
      Move16 = 16,
      Move17 = 17,
      Move18 = 18,
      Move19 = 19,
      Move20 = 20,
      Move30 = 30,
      Move40 = 40,
      Move50 = 50,
      Move60 = 60,
      Move70 = 70,
      Move80 = 80,
      Move90 = 90,
      Move100 = 100
    };

    /**
     * @Brief: Factions enum contains the factions for the game.
     */
    enum Faction {
      Player, Enemy
    };

    /**
     * @Brief: AmmoType enum contains the default ammo types.
     */
    enum AmmoType {
      TypeLaser, TypeMissile
    };

    /**
     * @Brief: AmmoDmgLvl enum contains the default ammo damage levels.
     */
    enum AmmoDmgLvl {
      Dmg01 = 1,
      Dmg02,
      Dmg03,
      Dmg04,
      Dmg05,
      Dmg06,
      Dmg07,
      Dmg08,
      Dmg09,
      Dmg10,
      Dmg20 = 20,
      Dmg30,
      Dmg40,
      Dmg50,
    };

    /**
     * @Brief: ShipClass enum contains the default ship classes.
     */
    enum ShipClass {
      Fighter, Bomber, Boss
    };

    /**
     * @Brief: ClassKilledScore enum contains the default score values for each ship class.
     */
    enum ClassKilledScore {
      FighterScore = 10,
      BomberScore = 100,
      BossScore = 500
    };

    /**
     * @Brief: ShipTypes enum contains the default ship types.
     */
    enum ShipTypes {
      // player
      Striker, // NightHawk,  Fury,
      // fighter
      Viper, Enforcer, // Sabre, Avenger, Nemesis,
      //bomber
      Bombardier, // Pummeler, Oblivion, Annihilator,
      //boss
      // Leviathan,
      Behemoth, // Colossus, Titan, Apocalypse
    };

    /**
     * @Brief: shipTypes map contains the default ship types.
     * @Note: The key is the enum ShipTypes and the value is the ship type name.
     * @Note: The ship type name is used to load the ship image from the resources.
     */
    const std::map<ShipTypes, QString> shipTypes = {
      //playerships
      {Striker,     "striker"},
//      {NightHawk,   "nighthawk"},
//      {Fury,        "fury"},
      // fighter ships
      {Viper,       "viper"},
      {Enforcer,    "enforcer"},
//      {Sabre,       "sabre"},
//      {Avenger,     "avenger"},
//      {Nemesis,     "nemesis"},
      // Bomber ships
      {Bombardier,  "bombardier"},
//      {Pummeler,    "pummeler"},
//      {Oblivion,    "oblivion"},
//      {Annihilator, "annihilator"},
      // Boss ships
//      {Leviathan,   "leviathan"},
      {Behemoth,    "behemoth"},
    };

    /**
     * @Brief: AnimationStates enum contains the default animation states.
     */
    enum AnimationStates {
      Cruising,
      Accelerating,
      Decelerating,
      Exploding
    };

    /**
     * @Brief: animationStates map contains the default animation states.
     * @Note: The key is the enum AnimationStates and the value is the animation state name.
     * @Note: The animation state name is used to load the animation image from the resources.
     */
    const std::map<AnimationStates, QString> animationStates = {
      {Cruising,     "cruising"},
      {Accelerating, "accelerating"},
      {Decelerating, "decelerating"},
      {Exploding,    "exploding"}
    };

    /**
     * @Brief: ShipFormations enum contains the default ship formations.
     * @Note: The formations are used to create the enemy ship wave formations.
     */
    const QList<QList<QList<bool>>> formations = {
      {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
      },
      {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
      },
      {
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0}
      },
      {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
      },
      {
        {0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0}
      },
      {
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0}
      },
      {
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0}
      },
      {
        {0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
      },
      {
        {0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
      },
      {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
      },
      {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
      },
      {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
      },
      {
        {1, 1, 1, 0, 0, 0, 1, 1, 1},
        {0, 0, 0, 1, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 1, 1, 0, 0, 1},
        {0, 1, 0, 1, 1, 1, 0, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0}
      },
      {
        {0, 0, 1, 1, 0, 1, 1, 0, 0},
        {0, 1, 0, 1, 1, 1, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 0, 1, 1, 1, 0, 1, 0},
        {0, 0, 1, 1, 0, 1, 1, 0, 0}
      },
      {
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 1}
      },
      {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
      },
      {
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 1, 0, 1, 1, 0},
        {1, 1, 0, 1, 0, 1, 0, 1, 1},
      },
      {
        {0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0},
      },
      {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
      {
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 1, 1, 0, 0},
        {0, 1, 0, 1, 1, 1, 0, 1, 0},
        {1, 0, 1, 1, 0, 1, 1, 0, 1},
        {0, 1, 0, 1, 1, 1, 0, 1, 0},
      },
    };



    /**
     * @brief The ShipTypes enum
     */
    extern const QList<QString> ammoLasers;

    /**
     * @brief The ShipTypes enum
     */
    extern const QList<QString> ammoMissiles;

    /**
     * @brief getShipAnimation
     * @details This function returns a QList<QString> of image paths for the
     * requested ship animation. The path is constructed from the shipType and
     * animState parameters.
     * @param shipType
     * @param animState
     * @return QList<QString> of image paths for the requested ship animation
     */
    extern QList<QString> getShipAnimation(ShipTypes shipType, AnimationStates animState);

    /**
     * @brief randomBool
     * @details This function returns a random boolean value.
     * @return random boolean value
     */
    extern bool randomBool();
  }; // space_pewpew
}
#endif //METODIK_INVADERS2_SETTINGS// _H