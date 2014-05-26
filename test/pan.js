function pan(texture, width, height) {
  PIXI.TilingSprite.call(this, texture, width, height);
  
  this.position.x = 0;
  this.position.y = 0;
  this.tilePosition.x = 0;
  this.tilePosition.y = 0;
}

pan.constructor = pan;
pan.prototype = Object.create(PIXI.TilingSprite.prototype);