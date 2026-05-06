# DAA-MP-2026
# Personalized Study Planner
A **console-based study planner in C++** that intelligently generates a personalized study schedule using **Design and Analysis of Algorithms (DAA)** concepts.

This project applies **Merge Sort + Greedy (Fractional Knapsack)** to optimize how a student should allocate limited study hours across multiple topics.

---

## Problem Statement

Students often struggle with:
- Too many topics and limited time
- Unclear prioritization
- Inefficient scheduling

This project solves that by:

✔ Assigning priority to each topic  
✔ Selecting the most important topics first  
✔ Distributing them across available study hours  

---

## Core Logic (Exactly How the System Works)

### Priority Calculation

Each topic is evaluated using:
Priority = (0.5 × Difficulty + 0.5 × Weightage) / Deadline

Ratio = Priority / TimeRequired

- Higher difficulty + weightage → higher importance  
- Shorter deadline → higher urgency  
- Less time required → more efficient  

Final decision is based on **priority-to-time ratio**

---

### Sorting (Merge Sort)

- Topics are sorted in **descending order of ratio**
- Implemented manually using **Merge Sort**
- Ensures optimal ordering before selection

---

### 🎒 Topic Selection (Fractional Knapsack)

- Total available study hours = sum of daily hours
- Topics are selected greedily:
  - Full topic if time allows
  - Partial topic if time is limited

This maximizes productivity within constraints

---

### 📅 Schedule Generation

- Converts selected topics into:
  - **Hour-wise slots**
  - **Day-wise distribution**

Example:
Day 1:
Hour 1 → DAA-Greedy
Hour 2 → OS-Scheduling


---

## Project Structure

### `Topic` Class
Handles:
- Input of topic details
- Priority calculation
- Tracking hours allocated

---

### `FileManager` Class
Handles:
- Checking if student exists
- Writing topics to file (`topics.txt`)
- Appending new topics
- Loading topics for scheduling

Data format in file:
Student username
subject topic difficulty weightage deadline time
...
END


---

### `Scheduler` Class
Handles:
- Merge Sort implementation
- Fractional Knapsack logic
- Final schedule creation

---

## Data Persistence

- File used: `topics.txt`
- Supports **multiple students**
- Each student's data is stored separately.

  
---

## How to Run

### Step 1: Compile
```bash
g++ daa.cpp -o planner
```
Step 2: Run
```bash
./planner
```
