data:extend({
    {
        type = "entity",
        name = "player",
        SpawnPosition = {X = 10, Y = 20},
        Sprite = {
            Width = 64,
            Height = 58,
            XScale = 1,
            YScale = 1,
            TextureId = "player",
            DefaultFlip = "none"
        },
        Animations = {
            DefaultAnimation = AnimationType.IDLE,
            Elements = {
                {
                    Type = AnimationType.IDLE,
                    Source = "content/assets/graphics/character/edge/idle.png",
                    TextureId = "player",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 12,
                    Speed = 85,
                    Loop = true
                }, {
                    Type = AnimationType.RUN,
                    Source = "content/assets/graphics/character/edge/walk.png",
                    TextureId = "player_run",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }, {
                    Type = AnimationType.JUMP,
                    Source = "content/assets/graphics/character/edge/jump.png",
                    TextureId = "player_jump",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }, {
                    Type = AnimationType.ATTACK,
                    Source = "content/assets/graphics/character/edge/attack.png",
                    TextureId = "player_attack",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }, {
                    Type = AnimationType.CROUCH,
                    Source = "content/assets/graphics/character/edge/slide.png",
                    TextureId = "player_crouch",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }, {
                    Type = AnimationType.FALL,
                    Source = "content/assets/graphics/character/edge/fall.png",
                    TextureId = "player_fall",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }
            }
        },
        RigidBody =
        {
            Mass = 10.0,
            Gravity = 9.8,
            RunSpeed = 60.0,
            JumpForce = 185.0,
            JumpTime = 25.0,
            AttackTime = 20.0,
            ColliderBuffer =
            {
                X = 17,
                Y = 0,
                Width = 44,
                Height = 41
            }
        },
        Commands =
        {
            Enabled = true
        }
    }
})
