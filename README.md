# CS Playground

Welcome to **CS Playground**, a growing collection of competitive-programming solutions, algorithm experiments, and creative coding projects spanning C++, Java, Python, and JavaScript. Whether you are looking for reference implementations, learning materials, or inspiration for your next hackathon, this repository gathers the author's journey through problem solving, visual computing, and applied AI.

## Why explore this repo?
- **Hundreds of algorithmic solutions** across Codeforces and USACO help you compare approaches, study patterns, and sharpen your contest strategies.【F:codeforces/1A.cpp†L1-L12】【F:usaco/LoanRepayment.cpp†L1-L33】
- **Cross-language data structure implementations** showcase how core concepts translate between Java and C++, including heaps, search strategies, and sorting visualizations.【F:java/HeapSort.java†L1-L92】【F:random c++/quicksort.cpp†L1-L57】
- **Interactive applications** highlight the fun side of coding, from a Perlin-noise Minecraft clone to a three.js quote generator and math-focused GUIs.【F:python/games/minecraft.py†L1-L100】【F:javascript/webdev/hackathon1/script.js†L1-L189】【F:python/polynomial_gui.py†L1-L110】
- **Applied machine learning experiments** document model training and conversion workflows for robotics and computer vision projects.【F:python/ftc ai/train.py†L1-L11】

## Repository tour

| Directory | What's inside |
|-----------|----------------|
| `codeforces/` | Solutions to Codeforces problems organized by contest ID, illustrating patterns like binary search, greedy, and dynamic programming.【F:codeforces/1A.cpp†L1-L12】 |
| `usaco/` | Implementations for USACO practice sets in both C++ and Java, often with reusable helper utilities such as fast I/O and binary search templates.【F:usaco/LoanRepayment.cpp†L1-L33】 |
| `random c++/` | Standalone algorithm demos (quicksort, radix sort, bit manipulation, etc.) useful for benchmarking and interview prep.【F:random c++/quicksort.cpp†L1-L57】 |
| `java/` | Data-structure and algorithm practice in Java, including heaps, trees, string statistics, and utility classes like ASCII art converters.【F:java/HeapSort.java†L1-L92】 |
| `python/` | A mix of math tools, calculators, AI experiments, and GUI prototypes—including the polynomial factorizer, Ursina-based games, and YOLO workflows.【F:python/polynomial_gui.py†L1-L110】【F:python/games/minecraft.py†L1-L100】【F:python/ftc ai/train.py†L1-L11】 |
| `javascript/webdev/` | Web experiments such as the hackathon quote generator that combines three.js visuals with external data sources.【F:javascript/webdev/hackathon1/index.html†L1-L18】【F:javascript/webdev/hackathon1/script.js†L1-L189】 |

## Featured projects

### Competitive programming notebooks
- The Codeforces folder captures quick, idiomatic implementations—from floor tiling math (`1A.cpp`) to prefix-sum manipulations—ideal for reviewing patterns before a contest.【F:codeforces/1A.cpp†L1-L12】
- USACO solutions include annotated binary search strategies like the loan repayment solver, helping you compare time-complexity trade-offs between languages.【F:usaco/LoanRepayment.cpp†L1-L33】

### Algorithm playgrounds
- Java's `HeapSort` class not only sorts but also measures runtime and offers randomized input generation for experimentation.【F:java/HeapSort.java†L1-L92】
- The C++ quicksort demo applies median-of-three pivot selection, custom random-array generation, and console visualization to illustrate algorithm tuning.【F:random c++/quicksort.cpp†L1-L57】

### Creative coding & visualization
- `python/games/minecraft.py` recreates chunked terrain generation with Perlin noise, threaded chunk loading, and gravity for a lightweight voxel world.【F:python/games/minecraft.py†L1-L100】
- `javascript/webdev/hackathon1` blends a dynamic three.js particle field with a CSV-powered motivational quote generator and typewriter effects for UI polish.【F:javascript/webdev/hackathon1/script.js†L1-L189】【F:javascript/webdev/hackathon1/styles.css†L1-L66】
- `python/polynomial_gui.py` provides a Tkinter interface for factoring polynomials, solving for roots, and filtering solutions by type using SymPy.【F:python/polynomial_gui.py†L1-L110】

### Robotics & AI experiments
- The `python/ftc ai` toolkit documents YOLOv8 fine-tuning plus conversion utilities for ONNX and TensorFlow Lite deployment, streamlining FTC robotics pipelines.【F:python/ftc ai/train.py†L1-L11】

## Getting started

### Run a C++ solution
```bash
g++ -std=c++17 codeforces/1A.cpp -o 1A
./1A <<<'6 6 4'
```

### Experiment with Java algorithms
```bash
javac java/HeapSort.java
java HeapSort
```

### Launch the polynomial factorizer GUI
```bash
python3 python/polynomial_gui.py
```
> The script will automatically install SymPy if it is missing and then open a Tkinter window for factoring and root analysis.【F:python/polynomial_gui.py†L7-L110】

### Explore the quote generator
Open `javascript/webdev/hackathon1/index.html` in your browser to see the animated particle field and interactive quote typing effect.【F:javascript/webdev/hackathon1/index.html†L1-L18】【F:javascript/webdev/hackathon1/script.js†L1-L189】

## Contributing & extending
1. **Fork & branch** – Create a feature branch per topic (e.g., `feature/new-dp-solution`).
2. **Document your approach** – Add comments or markdown notes describing problem statements or algorithmic insights.
3. **Add test inputs** – Provide sample inputs/outputs or driver code where applicable so others can reproduce your results.
4. **Submit a pull request** – Summarize the learning objective and any references used.

Not sure where to start? Consider porting a favorite algorithm between languages, adding visualizations to existing solvers, or contributing write-ups that explain tricky contest problems.

## Stay in touch
If you find the repository helpful, give it a ⭐️, share it with teammates, or open an issue with ideas for future explorations. Collaboration and feedback are always welcome—this playground grows stronger with every contribution!
