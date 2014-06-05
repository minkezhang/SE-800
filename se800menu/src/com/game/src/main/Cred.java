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
	public Rectangle bgmb = new Rectangle(600,20,20,20);
	public Rectangle selbgmb = new Rectangle(600,20,20,20);
	
	Game game;
	
	public Cred(Game game){
		this.game = game;
	}
	
	public void render(Graphics g, int key){
		Graphics2D g2d = (Graphics2D) g;
		
		Color top = new Color(250, 125, 125, 105);
		Color bot = new Color(0,0,0,175);
		Color high = new Color(125, 250, 250, 195);
		if(this.game.bgmon == true){
			g.setColor(top);
			g2d.draw(selbgmb);
			g2d.fill(selbgmb);
			}
		if(key==1){
		g.setColor(high);
		g2d.draw(select);
		g2d.fill(select);
		}
		g.setColor(top);
		Font fnt0 = new Font("arial", Font.PLAIN, 15);
		g.setFont(fnt0);
		g.drawString("BGM",bgmb.x-38,bgmb.y+16);
		g2d.draw(bgmb);
		Font fnt1 = new Font("arial", Font.BOLD, 30);
		g.setFont(fnt1);
		g.drawString("<<Back",back.x+1,back.y+36);
		g2d.draw(back);
		g2d.draw(body);
		g.setColor(bot);
		g2d.fill(body);
		g.setColor(top);
		g.setFont(new Font("arial", Font.PLAIN,20));
		g.drawString("SE-800 ",body.x+5,body.y+30);
		g.drawString("Group 329 Game Construction CMSC 23800 (C) 2014",body.x+5,body.y+50);
		g.drawString("Not for Commercial Use",body.x+5,body.y+70);
		g.drawString("Steven Garcia: Asset Modeling, Physics",body.x+5,body.y+100);
		g.drawString("Eric Guan: AI",body.x+5,body.y+140);
		g.drawString("Justin Lang: AI",body.x+5,body.y+180);
		g.drawString("Laura Macaddino: Rendering, Networks, Audio",body.x+5,body.y+220);
		g.drawString("Seun Ogedengbe: Menu, Audio",body.x+5,body.y+260);
		g.drawString("Minke Zhang: Physics, Interface, Rendering",body.x+5,body.y+300);
	}
	
}
