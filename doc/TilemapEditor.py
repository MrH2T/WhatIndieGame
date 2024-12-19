import tkinter as tk
from tkinter import filedialog, messagebox
from PIL import Image, ImageTk

CANVAS_WIDTH=2000
CANVAS_HEIGHT=1500
SELECT_WIDTH=1000
SELECT_HEIGHT=3000
TILE_DRAW=50

class TilemapAssistant:
    def __init__(self, master):
        self.master = master
        self.master.title("Tilemap Create Assistant")

        self.tile_width = 32  # Default tile width
        self.tile_height = 32  # Default tile height
        self.tiles = []
        self.selected_tile = None
        self.canvas_images = []  # Store images placed on the canvas
        self.scaled_tile_images = []  # Store scaled images for the tile area

        self.setup_ui()

    def setup_ui(self):
        self.left_frame = tk.Frame(self.master)
        self.left_frame.pack(side=tk.LEFT, padx=10, pady=10)

        self.right_frame = tk.Frame(self.master)
        self.right_frame.pack(side=tk.RIGHT, padx=10, pady=10)

        self.h_scrollbar_canvas=tk.Scrollbar(self.right_frame,orient=tk.HORIZONTAL)
        self.h_scrollbar_canvas.pack(side=tk.BOTTOM,fill=tk.X)
        self.v_scrollbar_canvas=tk.Scrollbar(self.right_frame,orient=tk.VERTICAL)
        self.v_scrollbar_canvas.pack(side=tk.RIGHT,fill=tk.Y)

        self.canvas = tk.Canvas(self.right_frame, width=640, height=480, bg='white',scrollregion=(0,0,CANVAS_WIDTH,CANVAS_HEIGHT),xscrollcommand=self.h_scrollbar_canvas.set,yscrollcommand=self.v_scrollbar_canvas.set)
        self.canvas.pack(side=tk.LEFT,fill=tk.BOTH,expand=True)
        self.v_scrollbar_canvas.config(command=self.canvas.yview)
        self.h_scrollbar_canvas.config(command=self.canvas.xview)

        # Create a frame for the tile area to include scrollbars
        self.tile_frame = tk.Frame(self.left_frame)
        self.tile_frame.pack()

        # Add scrollbars
        self.v_scrollbar = tk.Scrollbar(self.tile_frame, orient=tk.VERTICAL)
        self.v_scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        self.h_scrollbar = tk.Scrollbar(self.tile_frame, orient=tk.HORIZONTAL)
        self.h_scrollbar.pack(side=tk.BOTTOM, fill=tk.X)
        
        # Create a canvas for the tile area
        self.tile_area = tk.Canvas(self.tile_frame, bg='lightgrey', scrollregion=(0, 0, SELECT_WIDTH, SELECT_HEIGHT))
        self.tile_area.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        # Configure the scrollbars
        self.tile_area.config(yscrollcommand=self.v_scrollbar.set)
        self.tile_area.config(xscrollcommand=self.h_scrollbar.set)
        self.v_scrollbar.config(command=self.tile_area.yview)
        self.h_scrollbar.config(command=self.tile_area.xview)

        self.load_button = tk.Button(self.master, text="Load Tile Bitmap", command=self.load_image)
        self.load_button.pack(pady=10)

        self.export_button = tk.Button(self.master, text="Export Tile Map", command=self.export_tilemap)
        self.export_button.pack(pady=10)

        self.canvas.bind("<Button-1>", self.place_tile)
        self.canvas.bind("<Button-3>", self.erase_tile)
        self.tile_area.bind("<Button-1>", self.select_tile)

        self.tilemap = []

    def load_image(self):
        file_path = filedialog.askopenfilename(title="Select Tile Bitmap", filetypes=[("Bitmap files", "*.bmp")])
        if file_path:
            self.prompt_tile_dimensions(file_path)

    def prompt_tile_dimensions(self, file_path):
        dimension_window = tk.Toplevel(self.master)
        dimension_window.title("Tile Dimensions")

        tk.Label(dimension_window, text="Enter tile width:").pack()
        width_entry = tk.Entry(dimension_window)
        width_entry.pack()

        tk.Label(dimension_window, text="Enter tile height:").pack()
        height_entry = tk.Entry(dimension_window)
        height_entry.pack()

        def on_submit():
            try:
                self.tile_width = int(width_entry.get())
                self.tile_height = int(height_entry.get())
                self.create_tiles(file_path)
                dimension_window.destroy()
            except ValueError:
                messagebox.showerror("Error", "Please enter valid integer values for width and height.")

        submit_button = tk.Button(dimension_window, text="Submit", command=on_submit)
        submit_button.pack(pady=10)

    def create_tiles(self, file_path):
        # Load the image and get tile dimensions
        img = Image.open(file_path)
        img = img.convert("RGBA")  # Ensure the image is in RGBA mode
        img_width, img_height = img.size

        # Clear previous tiles
        self.tiles.clear()
        self.canvas_images.clear()  # Clear previous image references
        self.tile_area.delete("all")
        self.scaled_tile_images.clear()  # Clear previous scaled images

        # Calculate the number of rows and columns
        self.tiles_per_row = img_width // self.tile_width
        self.tiles_per_column = img_height // self.tile_height

        # Extract tiles from the image
        for row in range(self.tiles_per_column):
            for col in range(self.tiles_per_row):
                x = col * self.tile_width
                y = row * self.tile_height

                # Ensure we're within image bounds
                if (x + self.tile_width <= img_width) and (y + self.tile_height <= img_height):
                    tile = img.crop((x, y, x + self.tile_width, y + self.tile_height))
                    self.tiles.append(tile)

                    # Convert to PhotoImage and store it to prevent garbage collection
                    tile_image = ImageTk.PhotoImage(tile)
                    
                    # Create a scaled version to display in the tile area (double the size)
                    scaled_tile_image = tile.resize((TILE_DRAW,TILE_DRAW), Image.LANCZOS)
                    scaled_photo_image = ImageTk.PhotoImage(scaled_tile_image)

                    self.scaled_tile_images.append(scaled_photo_image)  # Store reference to avoid garbage collection
                    # Draw the scaled tile in the selection area
                    self.tile_area.create_image(col * TILE_DRAW, row * TILE_DRAW, anchor=tk.NW, image=scaled_photo_image)

                    # Draw a border around the scaled tile based on user inputs
                    self.tile_area.create_rectangle(col * TILE_DRAW, row * TILE_DRAW, 
                                                    col * TILE_DRAW + TILE_DRAW, row * TILE_DRAW + TILE_DRAW, outline="black")

    def select_tile(self, event):
        x = (event.x+int(self.h_scrollbar.get()[0]*SELECT_WIDTH)) // TILE_DRAW  
        y = (event.y+int(self.v_scrollbar.get()[0]*SELECT_HEIGHT)) // TILE_DRAW 
        tile_index = y * self.tiles_per_row + x

        if 0 <= tile_index < len(self.tiles):
            self.selected_tile = tile_index

    def place_tile(self, event):
        if self.selected_tile is not None:
            x = (event.x+int(self.h_scrollbar_canvas.get()[0]*CANVAS_WIDTH)) // TILE_DRAW * TILE_DRAW
            y = (event.y+int(self.v_scrollbar_canvas.get()[0]*CANVAS_HEIGHT)) // TILE_DRAW * TILE_DRAW
            tile_row = y // TILE_DRAW
            tile_col = x // TILE_DRAW

            while True:
                if not (0<=tile_row<len(self.tilemap)): break
                if not (0<=tile_col<len(self.tilemap[tile_row])): break

                self.canvas.delete(self.tilemap[tile_row][tile_col][1])
                self.tilemap[tile_row][tile_col]=(-1,0) 
                
                while len(self.tilemap[tile_row])>0 :
                    if self.tilemap[tile_row][-1][0]==-1:
                        self.tilemap[tile_row].pop()
                    else:
                        break
                while len(self.tilemap)>0 :
                    if len(self.tilemap[-1])==0:
                        self.tilemap.pop()
                    else:
                        break
                break

            # Place the original-sized tile on the canvas
            tile_image = ImageTk.PhotoImage(self.tiles[self.selected_tile])
            if tile_image == None:
                return
            scaled_tile_image = self.tiles[self.selected_tile].resize((TILE_DRAW,TILE_DRAW), Image.LANCZOS)
            scaled_photo_image = ImageTk.PhotoImage(scaled_tile_image)

            image_id = self.canvas.create_image(x, y, anchor=tk.NW, image=scaled_photo_image)
            self.canvas_images.append((image_id,scaled_photo_image))

            # Store the image reference to prevent garbage collection
            # Update tilemap

            while len(self.tilemap) <= tile_row:
                self.tilemap.append([])

            while len(self.tilemap[tile_row]) <= tile_col:
                self.tilemap[tile_row].append((-1,0))  # Mark empty spots

            self.tilemap[tile_row][tile_col] = (self.selected_tile,image_id) # Store the tile index
    def erase_tile(self,event):
        x = (event.x+int(self.h_scrollbar_canvas.get()[0]*CANVAS_WIDTH)) // TILE_DRAW * TILE_DRAW
        y = (event.y+int(self.v_scrollbar_canvas.get()[0]*CANVAS_HEIGHT)) // TILE_DRAW * TILE_DRAW
        tile_row=y//TILE_DRAW
        tile_col=x//TILE_DRAW
        if not (0<=tile_row<len(self.tilemap)): return
        if not (0<=tile_col<len(self.tilemap[tile_row])): return

        self.canvas.delete(self.tilemap[tile_row][tile_col][1])
        self.tilemap[tile_row][tile_col]=(-1,0) 
        
        while len(self.tilemap[tile_row])>0 :
            if self.tilemap[tile_row][-1][0]==-1:
                self.tilemap[tile_row].pop()
            else:
                break
        while len(self.tilemap)>0 :
            if len(self.tilemap[-1])==0:
                self.tilemap.pop()
            else:
                break

    def export_tilemap(self):
        filename = filedialog.asksaveasfilename(defaultextension=".txt",
                                                  filetypes=[("Text files", "*.txt"),
                                                             ("All files", "*.*")])
        if filename:
            with open(filename, 'w') as file:
                # Format output as {{0,0,1,1,0},{1,1,3,3,2}}
                file.write('{' + ','.join('{' + ','.join(str(item[0]) for item in row) + '}' for row in self.tilemap) + '}')
                file.write('R'+str(len(self.tilemap))+'C'+str(len(self.tilemap[0])))
            messagebox.showinfo("Export Complete", f"Tile map exported to {filename}")
            

if __name__ == "__main__":
    root = tk.Tk()
    app = TilemapAssistant(root)
    root.mainloop()