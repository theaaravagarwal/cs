import torch
from diffusers import DiffusionPipeline, LCMScheduler
import matplotlib.pyplot as plt
size = 2048
num_inference_steps = 10
guidance_scale = 0.0
def load_dreamshaper_lora_pipeline():
    pipeline = DiffusionPipeline.from_pretrained("Lykon/dreamshaper-7")
    if torch.cuda.is_available():
        pipeline.to("cuda")
    pipeline.scheduler = LCMScheduler.from_config(pipeline.scheduler.config)
    pipeline.load_lora_weights("latent-consistency/lcm-lora-sdv1-5")
    return pipeline
def ask_for_prompt():
    prompt = input("What do you want to create?\n")
    return prompt
def generate_images(pipeline, prompt, num_inference_steps, guidance_scale, size):
    results = pipeline(
        prompt=prompt,
        num_inference_steps=num_inference_steps,
        guidance_scale=guidance_scale,
        height=size,
        width=size
    )
    return results
def show_image(results):
    fig, ax = plt.subplots(figsize=(30, 30))
    ax.imshow(results.images[0])
    ax.axis('off')
    plt.subplots_adjust(left=0, right=1, top=1, bottom=0)
    plt.show()
def main():
    pipeline = load_dreamshaper_lora_pipeline()
    prompt = ask_for_prompt()
    results = generate_images(pipeline, prompt, num_inference_steps, guidance_scale, size)
    show_image(results)
if __name__ == "__main__":
    main()
