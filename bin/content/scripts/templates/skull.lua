data:extend({
    {
        type = "entity",
        name = "skull",
        SpawnPosition = {X = 100, Y = 20},
        Sprite = {
            Width = 128,
            Height = 108,
            XScale = 1,
            YScale = 1,
            TextureId = "skull",
            DefaultFlip = "none"
        },
        Animations = {
            DefaultAnimation = AnimationType.IDLE,
            Elements = {
                {
                    Type = AnimationType.IDLE,
                    Source = "content/assets/graphics/ennemis/skull/idle.png",
                    TextureId = "skull",
                    FrameWidth = 128,
                    FrameHeight = 108,
                    SpriteRowIndex = 1,
                    FrameCount = 12,
                    Speed = 100,
                    Loop = true
                }, {
                    Type = AnimationType.RUN,
                    Source = "content/assets/graphics/ennemis/skull/walk.png",
                    TextureId = "skull_run",
                    FrameWidth = 128,
                    FrameHeight = 108,
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
                X = 50,
                Y = 15,
                Width = 40,
                Height = 75
            }
        }
    }
})
