package com.game.src.main;

//import java.awt.Rectangle;
//import java.awt.Rectangle;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import com.game.src.main.Game.STATE;

public class MouseInput implements MouseListener{
	
	Game game;
	
	public MouseInput(Game game){
		this.game = game;
	}

	@Override
	public void mouseClicked(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		int mx = e.getX();
		int my = e.getY();
		/**
		public Rectangle playbut = new Rectangle(Game.WIDTH/2 +120,150,100,50);
		public Rectangle helpbut = new Rectangle(Game.WIDTH/2 +120,250,100,50);
		public Rectangle quitbut = new Rectangle(Game.WIDTH/2 +120,350,100,50);
		public Rectangle back = new Rectangle(10,10,110,50);
		 */
		if(mx >= 600 && mx <= 620 && my >= 20 && my <= 40)
			if(this.game.bgmon==true){
				this.game.bgmon = false;
				this.game.clip.stop();
			}
			else{
				this.game.bgmon = true;
				this.game.clip.start();
			}
		if(Game.State == STATE.MENU){
		if(mx >= Game.WIDTH / 2 + 120 && mx <= Game.WIDTH/2 + 220){
			if(my >= 150 && my <= 200){
				//pressed play
				//Game.State = Game.STATE.GAME;
				Game.State = STATE.PLAY;//.openGAME("8000","127.0.0.1","BLUE");
			}else if(my >= 250 && my <= 300){
				//credits
				Game.State = STATE.CREDITS;
			}else if(my >= 350 && my <= 400){
				//quit game
				System.exit(1);
			}
		}
		/**
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
	public Rectangle submit = new Rectangle(210,350,110,50);
	public Rectangle bgmb = new Rectangle(600,20,20,20);
		*/
		}else if(Game.State == STATE.PLAY){
			if(mx >= 10 && mx <= 120 && my >= 10 && my <= 60)
				Game.State = STATE.MENU;
			else if(mx >= 210 && mx <= 285 && my >= 70 && my <= 110)
				this.game.host = true;
			else if(mx >= 310 && mx <= 385 && my >= 70 && my <= 110)
				this.game.host = false;
			else if(mx >= 210 && mx <= 290 && my >= 140 && my <= 180)
				this.game.host = this.game.host;//noop
			else if(mx >= 210 && mx <= 290 && my >= 210 && my <= 250)
				this.game.host = this.game.host;//noop
			else if(mx >= 210 && mx <= 270 && my >= 280 && my <= 320)
				this.game.color = "RED";
			else if(mx >= 290 && mx <= 350 && my >= 280 && my <= 320)
				this.game.color = "BLUE";
			else if(mx >= 370 && mx <= 430 && my >= 280 && my <= 320)
				this.game.color = "GREEN";
			else if(mx >= 450 && mx <= 510 && my >= 280 && my <= 320)
				this.game.color = "YELLOW";
			else if(mx >= 530 && mx <= 590 && my >= 280 && my <= 320)
				this.game.color = "ORANGE";
			else if(mx >= 210 && mx <= 320 && my >= 350 && my <= 400)
				this.game.openGAME(this.game.port,this.game.addr,this.game.color);
		}else if(Game.State == STATE.CREDITS){
			if(mx >= 10 && mx <= 120 && my >= 10 && my <= 60)
				Game.State = STATE.MENU;
		}
	}


	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

}
