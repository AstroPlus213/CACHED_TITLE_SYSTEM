SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for player_title
-- ----------------------------
DROP TABLE IF EXISTS `player_title`;
CREATE TABLE `player_title`  (
  `pid` int(11) UNSIGNED NOT NULL DEFAULT 0,
  `id` int(11) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`pid`, `id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = DYNAMIC;

SET FOREIGN_KEY_CHECKS = 1;
