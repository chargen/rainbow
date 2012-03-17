--! Transitions Demo: Kim
--!
--! Copyright 2012 Bifrost Entertainment. All rights reserved.
--! \author Tommy Nguyen

Kim = {}
Kim.__index = Kim

function Kim.new(sprite)
	local self = {}
	setmetatable(self, Kim)
	self.sprite = sprite

	-- Used to alternate between move and rotate.
	self.alternate = false

	-- Cache rainbow namespace.
	local rainbow = rainbow

	-- Move sprite to the centre of the screen.
	local screen = rainbow.platform.screen
	self.moving = rainbow.transition.move(self.sprite, screen.width * 0.5, screen.height * 0.5, 500)

	-- Subscribe this class to input events.
	rainbow.input.subscribe(self)

	return self
end

function Kim:touch_began(touches)
	-- Cache rainbow.transition namespace.
	local transition = rainbow.transition

	-- Cancel the previous transition.
	self.moving:cancel()

	if self.alternate then
		-- Rotate 360 degrees in 1 second. Linear effect.
		local angle = self.sprite:get_angle() + rainbow.math.radians(360)
		self.moving = transition.rotate(self.sprite, angle, 1000)
		self.alternate = false
	else
		-- Move to point in 0.5 seconds. Squared ease-in effect.
		for h,t in pairs(touches) do
			self.moving = transition.move(self.sprite, t.x, t.y, 500, transition.effects.easein_square)
			self.alternate = true
			break
		end
	end
end

-- We don't care about these events.

function Kim:key_down() end
function Kim:key_up() end
function Kim:touch_canceled() end
function Kim:touch_ended() end
function Kim:touch_moved() end