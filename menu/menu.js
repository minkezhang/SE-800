App = function()
{
    this.load = function()
    {
        wade.loadImage('assets/spaceparallax.png');	
		wade.preloadAudio('assets/metegt.aac',true,true);//bgm
	};

    this.init = function()
    {
        //init background
        var bg = new Sprite('',5);
        bg.setSize(640, 480)
        var animation = new Animation('assets/spaceparallax.png', 4, 1, 0.130, 1, 0, 2);
        animation.setBlending(true);
		bg.addAnimation('back', animation);
        this.symbolObject = new SceneObject(bg);
        wade.addSceneObject(this.symbolObject);
        bg.playAnimation('back');
		
		//title
        this.titleSpr = new TextSprite('SE-800', '144px Slider', 'white', 'center');
		this.titleObj = new SceneObject(this.titleSpr);
		wade.addSceneObject(this.titleObj);
		var posX = 0.5 * wade.getScreenWidth();
        var posY = 0.1 * wade.getScreenHeight();
        this.titleObj.moveTo(0, -75, 100000);
 
        // create a set of game options
        this.options = [];
		this.optsprs = [];
        for (var x=0; x < 5; x++)
        {
            this.optsprs[x] = new TextSprite('option', '18px Arial', 'gray','center');
			//this.optsprs[x].setPosition(wade.getScreenWidth()/2, (wade.getScreenHeight()/2) + (x * 20))
			this.options[x] = new SceneObject(this.optsprs[x]);
			//this.options[x].setPosition(wade.getScreenWidth()/2, (wade.getScreenHeight()/2) + (x * 20))
			this.options[x].onMouseOver = function()
			{
				// we access the sprite as wade.app.textSprite, because this function is not a member of App, so using this.textSprite wouldn't work
				wade.app.optsprs[x].setColor('orange');
			};
			this.options[x].onMouseOut = function()
			{
				// we access the sprite as wade.app.textSprite, because this function is not a member of App, so using this.textSprite wouldn't work
				wade.app.optsprs[x].setColor('gray');
			};
			this.options[x].onClick = function()
			{
				// we access the sprite as wade.app.textSprite, because this function is not a member of App, so using this.textSprite wouldn't work
				wade.app.optsprs[x].setColor('yellow');
			};
			// add the object to the scene
			wade.addSceneObject(this.options[x]);
			this.options[x].moveTo(0, (30) + (x * 40), 100000);
			// set our text object to listen for onClick events
			wade.addEventListener(this.options[x], 'onClick');
			wade.addEventListener(this.options[x], 'onMouseOut');
			wade.addEventListener(this.options[x], 'onMouseOver');
        }
		
        
    };
};