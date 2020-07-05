data:extend({
    {
        type = "entity",
        name = "player",
        SpawnPosition = {X = 10, Y = 20},
        Sprite = {
            Width = 128,
            Height = 116,
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
                    FrameWidth = 128,
                    FrameHeight = 116,
                    SpriteRowIndex = 1,
                    FrameCount = 12,
                    Speed = 85,
                    Loop = true
                }, {
                    Type = AnimationType.RUN,
                    Source = "content/assets/graphics/character/edge/walk.png",
                    TextureId = "player_run",
                    FrameWidth = 128,
                    FrameHeight = 116,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }, {
                    Type = AnimationType.JUMP,
                    Source = "content/assets/graphics/character/edge/jump.png",
                    TextureId = "player_jump",
                    FrameWidth = 128,
                    FrameHeight = 116,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }, {
                    Type = AnimationType.ATTACK,
                    Source = "content/assets/graphics/character/edge/attack.png",
                    TextureId = "player_attack",
                    FrameWidth = 128,
                    FrameHeight = 116,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 40,
                    Loop = true
                }, {
                    Type = AnimationType.CROUCH,
                    Source = "content/assets/graphics/character/edge/slide.png",
                    TextureId = "player_crouch",
                    FrameWidth = 128,
                    FrameHeight = 116,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }, {
                    Type = AnimationType.FALL,
                    Source = "content/assets/graphics/character/edge/fall.png",
                    TextureId = "player_fall",
                    FrameWidth = 128,
                    FrameHeight = 116,
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
            JumpForce = 200.0,
            JumpTime = 30.0,
            AttackTime = 20.0,
            ColliderBuffer =
            {
                X = 50,
                Y = 15,
                Width = 40,
                Height = 75
            }
        },
        Commands =
        {
            Enabled = true
        }
    }
})
