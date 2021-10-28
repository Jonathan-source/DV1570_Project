-- All assets.
assets = {
    type = "mesh", id = "monkey-mesh", file = "C:/Dev/DV1570_Project/Test_Project/Lua_Irrlicht_BTH_template/Monkey.obj"
    type = "texture", id = "monkey-texture", file = "C:/Dev/DV1570_Project/Test_Project/Lua_Irrlicht_BTH_template/Texture_Monkey.png"
}

-- Map properties.
tile_map = {

}

-- Player properties.
player = {
    tag = "player",
    transform = {
        position = { x = 0, y = 0, z = 0 },
        scale = { x = 1, y = 1, z = 1 },
        rotation = { x = 0, y = 0, z = 0 },
    },
    sprite = {
        texture_asset_id = "monkey-texture",
        width = 32,
        height = 32,
        rect_x = 0,
        rect_y = 0
    },
    animation =  {
        num_frames = 3,
        speed_rate = 10,
    },
    boxcollider = {

    },
    rigidbody = {

    }
}