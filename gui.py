import tkinter as tk  
from tkinter import messagebox  
from difflib import get_close_matches  
import re  
  
# Load dictionary from file  
dictionary_file = "dictionary.txt"  
try:  
    with open(dictionary_file) as f:  
        dictionary = set(word.strip().lower() for word in f)  
except FileNotFoundError:  
    print(f"Dictionary file '{dictionary_file}' not found!")  
    exit(1)  
  
# Function to remove symbols from input  
def clean_word(word):  
    return re.sub(r'[^a-zA-Z]', '', word).lower()  
  
# Function to check spelling  
def check_word():  
    word = entry.get().strip()  
    word = clean_word(word)  
      
    if not word:  
        messagebox.showinfo("Error", "Please enter a word!")  
        return  
  
    if word in dictionary:    
        result_label.config(text=f"{word} is spelled correctly",  
fg="green")    
    else:    
        # Suggest up to 3 closest matches    
        closest = get_close_matches(word, dictionary, n=3,  
cutoff=0.6)    
        if closest:    
            suggestions = ", ".join(closest)    
            result_label.config(text=f"{word} not found.\nDid  
you mean: {suggestions}?", fg="red")    
        else:    
            result_label.config(text=f"{word} not found and no  
suggestions available.", fg="red")  
  
# Tkinter GUI setup  
root = tk.Tk()  
root.title("Spell Checker")  
root.geometry("500x220")  
root.resizable(False, False)  
  
# GUI widgets  
tk.Label(root, text="Enter a word:", font=("Arial",  
14)).pack(pady=10)  
entry = tk.Entry(root, font=("Arial", 14), width=30)  
entry.pack(pady=5)  
  
tk.Button(root, text="Check", font=("Arial", 12), width=10,  
command=check_word).pack(pady=10)  
  
result_label = tk.Label(root, text="", font=("Arial", 12),  
wraplength=450, justify="center")  
result_label.pack(pady=10)  
  
# Run the GUI  
root.mainloop().
