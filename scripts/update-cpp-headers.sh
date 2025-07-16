#!/bin/bash
# update_headers.sh - Update header comments in all .cpp files
# Run this script from the scripts directory

# Change to the parent directory where the .cpp files are located
cd ..

for file in *.cpp; do
    if [ -f "$file" ]; then
        echo "Processing $file..."

        # Check if file already has the Douglas Wade Goodall copyright header
        if ! grep -q "Engineering's" "$file"; then
            echo "  Adding header to $file"

            # Create temporary file with new header
            {
echo "////////////////////////////////////////////////////////////////////"
echo "// ~/public_html/fw/$file $(date '+%Y-%m-%d %H:%M') dwg -             //"
echo "// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //"
echo "// This file is part of MultiWare Engineering's VPA and FrameWork //"
echo "////////////////////////////////////////////////////////////////////"
                cat "$file"
            } > "$file.tmp" && mv "$file.tmp" "$file"
        else
            echo "  $file already has copyright header, skipping"
        fi
    fi
done

echo "Header update complete!"
