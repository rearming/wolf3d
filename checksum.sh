MD5_SUM=$(md5sum wolf_config.wolf | cut -c -32)
if [ "$MD5_SUM" == "57c34e0fdfa64b2a5ffd6f09a163c6a1" ]; then
  echo "checksum correct"
  #make
else
  echo "incorrect config file checksum."
fi