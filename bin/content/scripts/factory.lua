Factory = {}
Factory.__index = Factory

function Factory:createPlayer(Player)
    local entity = currentManager:createEntity()
    local transform = Transform.new()
    transform.Position = vector2D.new(Player.SpawnPosition.X,
                                       Player.SpawnPosition.Y)
    currentManager:addComponent(entity, transform:type(), transform)

    local render = SpriteRenderer.new()
    render.width = Player.Sprite.Width
    render.height = Player.Sprite.Height
    render.scale = vector2D.new(Player.Sprite.XScale,Player.Sprite.YScale)
    render.textureId = Player.Sprite.TextureId
    render.flip = RenderFlip[Player.Sprite.DefaultFlip]
    currentManager:addComponent(entity, render:type(), render)

    local animation = SpriteAnimation.new()
    animation.width = Player.Animation.FrameWidth
    animation.height = Player.Animation.FrameHeight
    animation.rowCount = Player.Animation.SpriteRowIndex
    animation.frameCount = Player.Animation.FrameCount
    animation.speed = Player.Animation.Speed
    animation.loop = Player.Animation.Loop
    currentManager:addComponent(entity, animation:type(), animation)

    local rigidBody = RigidBody.new()
    rigidBody.mass = Player.RigidBody.Mass
    rigidBody.gravity = Player.RigidBody.Gravity
    currentManager:addComponent(entity, rigidBody:type(), rigidBody)

    currentManager:registerEntity(entity)
end
