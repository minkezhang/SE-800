package com.game.src.main;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;

public class Cred {
	//Credit Submenu
	public Rectangle back = new Rectangle(10,10,110,50);
	public Rectangle body = new Rectangle(10,100,Game.WIDTH/2 + 360,Game.HEIGHT/2+230);
	public Rectangle select = new Rectangle(10,10,110,50);
	
	
	public void render(Graphics g, int key){
		Graphics2D g2d = (Graphics2D) g;
		
		Color top = new Color(250, 125, 125, 105);
		Color bot = new Color(0,0,0,175);
		Color high = new Color(125, 250, 250, 195);
		if(key==1){
		g.setColor(high);
		g2d.draw(select);
		g2d.fill(select);
		}
		g.setColor(top);
		
		Font fnt1 = new Font("arial", Font.BOLD, 30);
		g.setFont(fnt1);
		g.drawString("<<Back",back.x+1,back.y+36);
		g2d.draw(back);
		g2d.draw(body);
		g.setColor(bot);
		g2d.fill(body);
		g.setColor(top);
		g.drawString("Credits:",body.x+5,body.y+30);
		g.drawString("Steven Garcia:",body.x+5,body.y+80);
		g.drawString("Eric Guan:",body.x+5,body.y+130);
		g.drawString("Justin Lang:",body.x+5,body.y+180);
		g.drawString("Laura Macaddino:",body.x+5,body.y+230);
		g.drawString("Seun Ogedengbe:",body.x+5,body.y+280);
		g.drawString("Minke Zhang:",body.x+5,body.y+330);
	}
	
}
