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
            DefaultAnimation = "idle",
            Elements = {
                {
                    Name = "idle",
                    Source = "assets/player/idle.png",
                    TextureId = "player",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 12,
                    Speed = 85,
                    Loop = true
                }, {
                    Name = "run",
                    Source = "assets/player/walk.png",
                    TextureId = "player_run",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }, {
                    Name = "jump",
                    Source = "assets/player/jump.png",
                    TextureId = "player_jump",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }, {
                    Name = "attack",
                    Source = "assets/player/attack.png",
                    TextureId = "player_attack",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }, {
                    Name = "crouch",
                    Source = "assets/player/slide.png",
                    TextureId = "player_crouch",
                    FrameWidth = 64,
                    FrameHeight = 58,
                    SpriteRowIndex = 1,
                    FrameCount = 8,
                    Speed = 100,
                    Loop = true
                }, {
                    Name = "fall",
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
        RigidBody = {Mass = 1.0, Gravity = 0.5},
        Commands = 
        {
            Enabled = true
        }
    }
})
