package com.game.src.main;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;

public class Play {
	//Credit Submenu
	//rectangle( x, y, width, height)
	public Rectangle back = new Rectangle(10,10,110,50);
	public Rectangle servme = new Rectangle(210,70,75,40);
	public Rectangle clieme = new Rectangle(310,70,75,40);
	public Rectangle porten = new Rectangle(210,140,80,40);
	public Rectangle addren = new Rectangle(210,210,80,40);
	public Rectangle cred = new Rectangle(210,280,60,40);
	public Rectangle cblu = new Rectangle(290,280,60,40);
	public Rectangle cgre = new Rectangle(370,280,60,40);
	public Rectangle cyel = new Rectangle(450,280,60,40);
	public Rectangle corg = new Rectangle(530,280,60,40);
	
	// RED, BLUE, GREEN, YELLOW, ORANGE
	
	//public Rectangle body = new Rectangle(10,100,Game.WIDTH/2 + 360,Game.HEIGHT/2+230);
	public Rectangle select = new Rectangle(10,10,110,50);
	public Rectangle submit = new Rectangle(210,350,110,50);
	
	Game game;
	
	public Play(Game game){
		this.game = game;
	}
	
	public void render(Graphics g, int key){
		Graphics2D g2d = (Graphics2D) g;
		
		Color top = new Color(250, 125, 125, 105);
		//Color bot = new Color(0,0,0,175);
		Color high = new Color(125, 250, 250, 195);
		g.setColor(high);
		switch(key){
		case 1:
			select.x = 10;
			select.y = 10;
			select.width = 110;
			select.height = 50;
			break;
		case 2:
			select.x = 210;
			select.y = 70;
			select.width = 75;
			select.height = 40;
			break;
		case 3:
			select.x = 310;
			select.y = 70;
			select.width = 75;
			select.height = 40;
			break;
		case 4:
			select.x = 210;
			select.y = 140;
			select.width = 80;
			select.height = 40;
			break;
		case 5:
			select.x = 210;
			select.y = 210;

			select.width = 80;
			select.height = 40;
			break;
		case 6:
			select.x = 208;
			select.y = 278;
			select.width = 64;
			select.height = 44;
			break;
		case 7:
			select.x = 288;
			select.y = 278;
			select.width = 64;
			select.height = 44;
			break;
		case 8:
			select.x = 368;
			select.y = 278;
			select.width = 64;
			select.height = 44;
			break;
		case 9:
			select.x = 448;
			select.y = 278;
			select.width = 64;
			select.height = 44;
			break;
		case 10:
			select.x = 528;
			select.y = 278;
			select.width = 64;
			select.height = 44;
			break;
		case 11:
			select.x = 210;
			select.y = 350;
			select.width = 110;
			select.height = 50;
			break;
		}
		g2d.draw(select);
		g2d.fill(select);
		
		g.setColor(top);
		
		Font fnt1 = new Font("arial", Font.BOLD, 30);
		g.setFont(fnt1);
		g.drawString("<<Back",back.x+1,back.y+36);
		g.drawString("Host Type",servme.x-200,servme.y+30);
		g.drawString("Port",porten.x-200,porten.y+30);
		g.drawString("Address",addren.x-200,addren.y+30);
		g.drawString("Ship Color",cred.x-200,cred.y+30);
		g.drawString("Submit",submit.x+4,submit.y+36);
		g2d.draw(back);
		if(this.game.host == true){
			g.setColor(new Color(225, 250, 150, 195));
			g2d.fill(servme);
		}
		g.setColor(top);
		g2d.draw(servme);
		if(this.game.host == false){
			g.setColor(new Color(225, 250, 150, 195));
			g2d.fill(clieme);
		}
		g.setColor(top);
		g2d.draw(clieme);
		g.drawString("Serv",servme.x+4,servme.y+30);
		g.drawString("Peer",clieme.x+4,servme.y+30);
		g2d.draw(porten);
		g2d.draw(addren);
		if(this.game.color == "RED")
			g.setColor(new Color(255, 50, 50, 255));
		else
		g.setColor(new Color(255, 0, 0, 195));
		g2d.draw(cred);
		g2d.fill(cred);
		if(this.game.color == "BLUE")
			g.setColor(new Color(50, 50, 255, 255));
		else
		g.setColor(new Color(0, 0, 255, 195));
		g2d.draw(cblu);
		g2d.fill(cblu);
		if(this.game.color == "GREEN")
			g.setColor(new Color(10, 255, 50, 255));
		else
		g.setColor(new Color(0, 255, 0, 195));
		g2d.draw(cgre);
		g2d.fill(cgre);
		if(this.game.color == "YELLOW")
			g.setColor(new Color(255, 255, 50, 255));
		else
		g.setColor(new Color(255, 255, 0, 195));
		g2d.draw(cyel);
		g2d.fill(cyel);
		if(this.game.color == "ORANGE")
			g.setColor(new Color(255, 128, 50, 255));
		else
		g.setColor(new Color(255, 128, 0, 195));
		g2d.draw(corg);
		g2d.fill(corg);
		g.setColor(top);
		g2d.draw(submit);
	}
	
}
