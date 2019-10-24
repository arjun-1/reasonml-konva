module Point = {
  [@bs.deriving abstract]
  type t = {
    x: float,
    y: float,
  };

  [@bs.send] external add: (t, t) => t = "add";

  [@bs.new] [@bs.module "paper"] external make: (float, float) => t = "Point";
};

module PathItem = {
  [@bs.deriving abstract]
  type t;

  [@bs.send] external moveTo: (t, Point.t) => unit = "moveTo";

  [@bs.send] external lineTo: (t, Point.t) => unit = "lineTo";
};

module Path = {
  [@bs.deriving abstract]
  type t = {mutable strokeColor: string};

  [@bs.send] external moveTo: (t, Point.t) => unit = "moveTo";

  [@bs.send] external lineTo: (t, Point.t) => unit = "lineTo";

  [@bs.new] [@bs.module "paper"] external make: unit => t = "Path";

  [@bs.new] [@bs.module "paper"] [@bs.scope "Path"]
  external circle: (Point.t, float) => t = "Circle";
};

module CompoundPath = {
  [@bs.deriving abstract]
  type t = {mutable strokeColor: string};

  [@bs.send] external moveTo: (t, Point.t) => unit = "moveTo";

  [@bs.send] external lineTo: (t, Point.t) => unit = "lineTo";

  [@bs.new] [@bs.module "paper"] external make: unit => t = "Compount";
};

[@bs.module "paper"] external setup: Webapi.Dom.Element.t => unit = "setup";
