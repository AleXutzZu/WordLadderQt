# 🧠 Word Ladder Game

A feature-rich desktop application implementing the classic **Word Ladder** puzzle game using **Qt (C++)**. It includes interactive gameplay, analysis tools, and player statistics, delivering both entertainment and insight.

## 📚 What Is Word Ladder?

**Word Ladder** is a word transformation game where players convert one word into another by changing a single letter at a time. Each intermediate word must be a valid dictionary word.

Example:

cold → cord → card → ward → warm

The goal is to find the **shortest transformation path** between two words.

## 🚀 Features

### 🔍 Analysis Mode

Explore the shortest path between any two valid words:

- Input a **start word** and a **target word**.
- The shortest transformation path is computed and displayed.
- The path is visualized in a **snake-style grid layout** with arrows indicating word progression.
- Great for understanding transformation logic and word relationships.

### 🎮 Play Mode

Engage in the word ladder challenge:

- Enter a **username** to start a new game.
- You are given two **random valid words** of the same length.
- Transform the start word into the target word by changing one letter at a time.
- Use the **Hint** button to see the next word in the optimal path.
- Tracks:
  - Number of moves
  - Hints used
  - Win/loss status

### 📊 Stats & Leaderboard

Keep track of player performance and competition:

- View statistics for any player:
  - Total **wins** and **losses**
  - **Win/loss ratio**
  - Date of last played game
- **Top 3 players** are displayed on a **visual podium**:
  - 🥇 Gold (1st place)
  - 🥈 Silver (2nd place)
  - 🥉 Bronze (3rd place)
- All data is saved per player in local CSV files and persists across sessions.

## 📸 Screenshots

<table>
  <tr>
    <td rowspan="2" style="width:50%;">
      <img src="https://github.com/user-attachments/assets/c9d979dc-7fd0-461d-b797-556827129177" alt="Analysis tab" style="width:100%;">
    </td>
    <td>
      <img src="https://github.com/user-attachments/assets/34bc7ed0-1d99-4e46-9ef7-9e0d81e49f30" alt="Stats tab" style="width:100%;">
    </td>
  </tr>
  <tr>
    <td>
      <img src="https://github.com/user-attachments/assets/4c984fb8-a187-4d0e-9998-bdbb0dd54810" alt="Playing a game" style="width:100%;">
    </td>
  </tr>
</table>





