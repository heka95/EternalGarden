data:extend({
    {
        type = "entity",
        name = "skull",
        SpawnPosition = {X = 100, Y = 20},
        Sprite = {
            Width = 768,
            Height = 54,
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
                    FrameWidth = 64,
                    FrameHeight = 54,
                    SpriteRowIndex = 1,
                    FrameCount = 12,
                    Speed = 100,
                    Loop = true
                }, {
                    Type = AnimationType.RUN,
                    Source = "content/assets/graphics/ennemis/skull/walk.png",
                    TextureId = "skull_run",
                    FrameWidth = 64,
                    FrameHeight = 54,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }
            }
        },
        RigidBody =
        {
            Mass = 65.0,
            Gravity = 9.807, -- Earth real gravity
            RunSpeed = 450.0,
            JumpForce = 1350.0,
            JumpTime = 20.0,
            AttackTime = 20.0,
            ColliderBuffer =
            {
                X = 17,
                Y = 0,
                Width = 44,
                Height = 41
            }
        }
    }
})
