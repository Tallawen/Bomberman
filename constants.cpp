#include "constants.h"

namespace Constants {

    namespace Video {

        ConstInt SCREEN_WIDTH("video.screen_width", 800);
        ConstInt SCREEN_HEIGHT("video.screen_height", 600);
        ConstStr SCREEN_TITLE("Bomberman");

    }

    namespace Menu {

        ConstInt SCREEN_WIDTH(456);
        ConstInt SCREEN_HEIGHT(456);
        ConstStr SCREEN_TITLE("Bomberman | menu");

    }

    namespace Player {

        ConstInt SPEED("player.speed", 100);
        ConstInt HEALTH("player.health", 5);
        ConstInt MAX_HEALTH("player.max_health", 5);
        ConstNum BLINK_TIME("player.blink_time", 1.0);
        ConstNum IMMORTAL_TIME("player.immortal_time", 6.0);

    }

    namespace Bomb {

        ConstInt START_AMOUNT("bomb.start_amount", 2);
        ConstInt MAX_AMOUNT("bomb.max_amount", 5);
        ConstNum LIFE_TIME("bomb.life_time", 2);

    }

    namespace Explosion {

        ConstInt LENGTH("explosion.length", 2);
        ConstNum DELAY("explosion.delay", 0.1f);

    }

    namespace Collectible {

        ConstNum MOVE_TIME("collectible.move_time", 1);
        ConstNum MOVE_DISTANCE("collectible.move_distance", 20);
        ConstNum BLINK_TIME("collectible.blink_time", 1);

    }

    namespace UI {

        namespace Avatar {

            ConstInt X("ui.avatar_x", 100);
            ConstInt Y("ui.avatar_y", 20);

        }

        namespace Scores {

            ConstInt X("ui.scores_x", 100);
            ConstInt Y("ui.scores_y", 20);

        }

        namespace HealthBar {

            ConstInt X("ui.healthBar_x", 100);
            ConstInt Y("ui.healthBar_y", 30);
            ConstInt LENGHT("ui.healthBar_lenght", 300);
            ConstInt ALPHA("ui.healthBar_alpha", 200);

        }

        namespace BombBar {

            ConstInt X("ui.bombBar_x", 100);
            ConstInt Y("ui.bombBar_y", 30);
            ConstInt OFFSET("ui.bombBar_offset", 100);
            ConstInt ALPHA("ui.healthBar_alpha", 100);

        }

        namespace FPS {

            ConstInt X("ui.fps_x", 300);
            ConstInt Y("ui.fps_y", 40);
            ConstInt SIZE("ui.fps_size", 20);

        }

    }

}
