rm -r ~/.pathy
mkdir ~/.pathy
mkdir ~/.pathy/pathy
cd ~/.pathy/pathy
wget https://raw.githubusercontent.com/science-penguin/Pathy/main/pathy
chmod +x pathy
if ! grep -q '?PATHYINSTALLED' "$HOME/.bashrc"
then
echo "#?PATHYINSTALLED-start" >> ~/.bashrc
echo "export PATH=\"\$HOME/.pathy/pathy:\$PATH\"" >> ~/.bashrc
echo "#?PATHYINSTALLED-end" >> ~/.bashrc
fi
echo "sed -i '/#?PATHYINSTALLED-start/,/#?PATHYINSTALLED-end/d' \"$HOME/.bashrc\";rm -rf ~/.pathy/pathy" > remove.sh