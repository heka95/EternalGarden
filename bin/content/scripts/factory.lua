Factory = {}
Factory.__index = Factory

function Factory:createPlayer(Player)
    local entity = currentManager:createEntity()
    local transform = Transform.new(vector2D.new(Player.SpawnPosition.X,
                                                 Player.SpawnPosition.Y))
    currentManager:addComponent(entity, transform:type(), transform)

    local render = SpriteRenderer.new(Player.Sprite.Width, Player.Sprite.Height,
                                      vector2D.new(Player.Sprite.XScale,
                                                   Player.Sprite.YScale),
                                      Player.Sprite.TextureId,
                                      RenderFlip[Player.Sprite.DefaultFlip])
    currentManager:addComponent(entity, render:type(), render)

    local animation = SpriteAnimation.new(Player.Animation.FrameWidth,
                                          Player.Animation.FrameHeight,
                                          Player.Animation.SpriteRowIndex,
                                          Player.Animation.FrameCount,
                                          Player.Animation.Speed,
                                          Player.Animation.Loop)
    currentManager:addComponent(entity, animation:type(), animation)

    currentManager:registerEntity(entity)
end