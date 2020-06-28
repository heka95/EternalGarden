data:extend({
    {
        type = "entity",
        name = "player",
        SpawnPosition = {X = 10, Y = 20},
        Sprite = {
            Width = 768,
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
                    Source = "assets/player/idle.png",
                    TextureId = "player",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 12,
                    Speed = 85,
                    Loop = true
                }, {
                    Type = AnimationType.RUN,
                    Source = "assets/player/walk.png",
                    TextureId = "player_run",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }, {
                    Type = AnimationType.JUMP,
                    Source = "assets/player/jump.png",
                    TextureId = "player_jump",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }, {
                    Type = AnimationType.ATTACK,
                    Source = "assets/player/attack.png",
                    TextureId = "player_attack",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }, {
                    Type = AnimationType.CROUCH,
                    Source = "assets/player/slide.png",
                    TextureId = "player_crouch",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }, {
                    Type = AnimationType.FALL,
                    Source = "assets/player/fall.png",
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
        RigidBody = {Mass = 1.0, Gravity = 3.5},
        Commands = 
        {
            Enabled = true
        }
    }
})
