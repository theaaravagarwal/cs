from ursina import *
from ursina.prefabs.first_person_controller import FirstPersonController
import numpy as np
from perlin_noise import PerlinNoise
import threading
import queue
import time

# Constants
CHUNK_SIZE = 16
BLOCK_SIZE = 1
RENDER_DISTANCE = 8  # In chunks

# Initialize Ursina
app = Ursina()

# Generate Perlin noise
noise = PerlinNoise(octaves=4, seed=42)

# Block Model
block_model = Entity(model='cube', color=color.white, scale=(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE))

# Generate Chunk Function
def generate_chunk(x_start, z_start, chunk_size, block_size):
    scale = 5.0  # Controls how stretched the terrain is
    height_scale = 10.0  # Controls the maximum height of the terrain
    chunk = []
    for x in range(chunk_size):
        for z in range(chunk_size):
            world_x = x_start + x
            world_z = z_start + z
            height = int(noise([world_x / scale, world_z / scale]) * height_scale)
            for y in range(max(0, height)):
                chunk.append((Vec3(world_x, y, world_z)))
    return chunk

# Draw a chunk function
def draw_chunk(chunk):
    for position in chunk:
        block = duplicate(block_model, position=position)
        block.color = color.color(0, 0, random.uniform(0.9, 1))

# Frustum culling
def in_frustum(camera_position, block_position, render_distance):
    dist = distance(camera_position, block_position)
    return dist < render_distance * CHUNK_SIZE

# Chunk loading thread
def chunk_loader(camera_position, loaded_chunks, chunk_queue):
    while True:
        center_chunk_x = int(camera_position.x // (CHUNK_SIZE * BLOCK_SIZE))
        center_chunk_z = int(camera_position.z // (CHUNK_SIZE * BLOCK_SIZE))
        for dx in range(-RENDER_DISTANCE, RENDER_DISTANCE + 1):
            for dz in range(-RENDER_DISTANCE, RENDER_DISTANCE + 1):
                chunk_key = (center_chunk_x + dx, center_chunk_z + dz)
                if chunk_key not in loaded_chunks:
                    x_start = (center_chunk_x + dx) * CHUNK_SIZE
                    z_start = (center_chunk_z + dz) * CHUNK_SIZE
                    chunk_data = generate_chunk(x_start, z_start, CHUNK_SIZE, BLOCK_SIZE)
                    chunk_queue.put((chunk_key, chunk_data))
        time.sleep(0.1)  # Allow the main thread to process

# Initialize Player
player = FirstPersonController()

# Physics (Gravity)
def apply_gravity(player, dt):
    player.y += -9.81 * dt
    if player.y < 0:
        player.y = 0

# Game loop update
def update():
    dt = time.dt

    apply_gravity(player, dt)

    # Add newly loaded chunks from the queue
    while not chunk_queue.empty():
        chunk_key, chunk_data = chunk_queue.get()
        loaded_chunks[chunk_key] = chunk_data
        draw_chunk(chunk_data)

    # Render visible chunks
    for chunk_key, chunk in list(loaded_chunks.items()):
        for block_pos in chunk:
            if in_frustum(player.position, block_pos, RENDER_DISTANCE):
                # Draw block in visible chunks (already done in draw_chunk)
                pass

# Initialize Chunk Loader
loaded_chunks = {}
chunk_queue = queue.Queue()
threading.Thread(target=chunk_loader, args=(player.position, loaded_chunks, chunk_queue), daemon=True).start()

# Start the game
app.run()


# this is very laggy btw
