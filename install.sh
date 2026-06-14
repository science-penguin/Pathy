rm -r ~/.pathy
mkdir ~/.pathy
mkdir ~/.pathy/pathy
cd ~/.pathy/pathy
wget https://raw.githubusercontent.com/science-penguin/Pathy/main/pathy
chmod +x pathy
echo "export PATH=\"\$HOME/.pathy/pathy:\$PATH\"" >> ~/.bashrc
