--TerainConfig.lua
-- List of parameters used in terrain generation
--[[
If LoadPerlin is set to true, a terrain algorithm will be used to generate the terrain and PerlinSize must be set to determin the world size. A good starting size is 4096


If LoadPerlin is set to false, the terrain factory will use the HeightMap image specified below to generate the terrain.
The terrain is divided into chunks that are loaded and unloaded as you move around the world, chunk size is used to determine how large these chunks are. A good starting size is 100.

--]]


LoadPerlin = true
PerlinSize = 4096

HeightMap = "res/images/test2.jpg"

ChunkSize = 100

GrassTexture = "grass"
WaterTexture = "water"
SandTexture = "sand"
DirtTexture = "dirt"
SnowTexture = "snow"

